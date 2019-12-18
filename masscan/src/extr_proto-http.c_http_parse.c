#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ProtocolState {unsigned int state; } ;
typedef  void InteractiveData ;
struct BannerOutput {int dummy; } ;
struct Banner1 {int /*<<< orphan*/  is_capture_html; int /*<<< orphan*/  html_fields; int /*<<< orphan*/  http_fields; } ;

/* Variables and functions */
#define  HTTPFIELD_CONTENT_LENGTH 131 
#define  HTTPFIELD_LOCATION 130 
 size_t HTTPFIELD_NEWLINE ; 
#define  HTTPFIELD_SERVER 129 
 size_t HTTPFIELD_UNKNOWN ; 
#define  HTTPFIELD_VIA 128 
 int /*<<< orphan*/  PROTO_HTML_FULL ; 
 int /*<<< orphan*/  PROTO_HTML_TITLE ; 
 int /*<<< orphan*/  PROTO_HTTP ; 
 size_t SMACK_NOT_FOUND ; 
 int /*<<< orphan*/  UNUSEDPARM (void*) ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  banout_append_char (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const) ; 
 int /*<<< orphan*/  isdigit (unsigned char const) ; 
 int /*<<< orphan*/  isspace (unsigned char const) ; 
 size_t smack_next_match (int /*<<< orphan*/ ,unsigned int*) ; 
 size_t smack_search_next (int /*<<< orphan*/ ,unsigned int*,unsigned char const*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  tcp_close (void*) ; 
 char toupper (unsigned char const) ; 

__attribute__((used)) static void
http_parse(
        const struct Banner1 *banner1,
        void *banner1_private,
        struct ProtocolState *pstate,
        const unsigned char *px, size_t length,
        struct BannerOutput *banout,
        struct InteractiveData *more)
{
    unsigned state = pstate->state;
    unsigned i;
    unsigned state2;
    unsigned log_begin = 0;
    unsigned log_end = 0;
    size_t id;
    enum {
        FIELD_START = 9,
        FIELD_NAME,
        FIELD_COLON,
        FIELD_VALUE,
        CONTENT,
        CONTENT_TAG,
        CONTENT_FIELD,
        
        DONE_PARSING
    };

    UNUSEDPARM(banner1_private);
    UNUSEDPARM(more);

    state2 = (state>>16) & 0xFFFF;
    id = (state>>8) & 0xFF;
    state = (state>>0) & 0xFF;

    for (i=0; i<length; i++)
    switch (state) {
    case 0: case 1: case 2: case 3: case 4:
        if (toupper(px[i]) != "HTTP/"[state]) {
            state = DONE_PARSING;
            tcp_close(more);
        } else
            state++;
        break;
    case 5:
        if (px[i] == '.')
            state++;
        else if (!isdigit(px[i])) {
            state = DONE_PARSING;
            tcp_close(more);
        }
        break;
    case 6:
        if (isspace(px[i]))
            state++;
        else if (!isdigit(px[i])) {
            state = DONE_PARSING;
            tcp_close(more);
        }
        break;
    case 7:
        /* TODO: look for 1xx response code */
        if (px[i] == '\n')
            state = FIELD_START;
        break;
    case FIELD_START:
        if (px[i] == '\r')
            break;
        else if (px[i] == '\n') {
            state2 = 0;
            state = CONTENT;
            log_end = i;
            banout_append(banout, PROTO_HTTP, px+log_begin, log_end-log_begin);
            log_begin = log_end;
            break;
        } else {
            state2 = 0;
            state = FIELD_NAME;
            /* drop down */
        }

    case FIELD_NAME:
        if (px[i] == '\r')
            break;
        id = smack_search_next(
                        banner1->http_fields,
                        &state2,
                        px, &i, (unsigned)length);
        i--;
        if (id == HTTPFIELD_NEWLINE) {
            state2 = 0;
            state = FIELD_START;
        } else if (id == SMACK_NOT_FOUND)
            ; /* continue here */
        else if (id == HTTPFIELD_UNKNOWN) {
            /* Oops, at this point, both ":" and "Server:" will match.
             * Therefore, we need to make sure ":" was found, and not
             * a known field like "Server:" */
            size_t id2;

            id2 = smack_next_match(banner1->http_fields, &state2);
            if (id2 != SMACK_NOT_FOUND)
                id = id2;

            state = FIELD_COLON;
        } else
            state = FIELD_COLON;
        break;
    case FIELD_COLON:
        if (px[i] == '\n') {
            state = FIELD_START;
            break;
        } else if (isspace(px[i])) {
            break;
        } else {
            //field_name(banout, id, http_fields);
            state = FIELD_VALUE;
            /* drop down */
        }

    case FIELD_VALUE:
        if (px[i] == '\r')
            break;
        else if (px[i] == '\n') {
            state = FIELD_START;
            break;
        }
        switch (id) {
        case HTTPFIELD_SERVER:
        case HTTPFIELD_LOCATION:
        case HTTPFIELD_VIA:
            //banner_append(&px[i], 1, banout);
            break;
        case HTTPFIELD_CONTENT_LENGTH:
                if (isdigit(px[i]&0xFF)) {
                    ; /*todo: add content length parsing */
                } else {
                    id = 0;
                }
            break;
        }
        break;
    case CONTENT:
        {
            unsigned next = i;

            id = smack_search_next(
                                   banner1->html_fields,
                                   &state2,
                                   px, &next, (unsigned)length);

            if (banner1->is_capture_html) {
                banout_append(banout, PROTO_HTML_FULL, &px[i], next-i);
            }

            if (id != SMACK_NOT_FOUND) {
                state = CONTENT_TAG;
            }

            i = next - 1;
        }
        break;
    case CONTENT_TAG:
        for (; i<length; i++) {
            if (banner1->is_capture_html) {
                banout_append_char(banout, PROTO_HTML_FULL, px[i]);
            }

            if (px[i] == '>') {
                state = CONTENT_FIELD;
                break;
            }
        }
        break;
    case CONTENT_FIELD:
        if (banner1->is_capture_html) {
            banout_append_char(banout, PROTO_HTML_FULL, px[i]);
        }
        if (px[i] == '<')
            state = CONTENT;
        else {
            banout_append_char(banout, PROTO_HTML_TITLE, px[i]);
        }
        break;
    case DONE_PARSING:
    default:
        i = (unsigned)length;
        break;
    }

    if (log_end == 0 && state < CONTENT)
        log_end = i;
    if (log_begin < log_end)
        banout_append(banout, PROTO_HTTP, px + log_begin, log_end-log_begin);



    if (state == DONE_PARSING)
        pstate->state = state;
    else
        pstate->state = (state2 & 0xFFFF) << 16
                | ((unsigned)id & 0xFF) << 8
                | (state & 0xFF);
}