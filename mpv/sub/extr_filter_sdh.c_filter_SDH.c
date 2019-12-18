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
struct sd {int dummy; } ;
struct buffer {char* string; int pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct sd*,char*) ; 
 char append (struct sd*,struct buffer*,char) ; 
 int /*<<< orphan*/  copy_ass (struct sd*,char**,struct buffer*) ; 
 int /*<<< orphan*/  init_buf (struct buffer*,scalar_t__) ; 
 int /*<<< orphan*/  remove_leading_hyphen_space (struct sd*,int,struct buffer*) ; 
 int /*<<< orphan*/  skip_bracketed (struct sd*,char**,struct buffer*) ; 
 int /*<<< orphan*/  skip_parenthesed (struct sd*,char**,struct buffer*) ; 
 int /*<<< orphan*/  skip_speaker_label (struct sd*,char**,struct buffer*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 
 char* talloc_strndup (int /*<<< orphan*/ *,char*,int) ; 

char *filter_SDH(struct sd *sd, char *format, int n_ignored, char *data, int length)
{
    if (!format) {
        MP_VERBOSE(sd, "SDH filtering not possible - format missing\n");
        return length ? talloc_strndup(NULL, data, length) : talloc_strdup(NULL, data);
    }

    // need null terminated string
    char *ass = length ? talloc_strndup(NULL, data, length) : data;

    int comma = 0;
    // scan format line to find the number of the field where the text is
    for (char *c = format; *c; c++) {
        if (*c == ',') {
            comma++;
            if (strncasecmp(c + 1, "Text", 4) == 0)
                break;
        }
    }
    // if preprocessed line some fields are skipped
    comma -= n_ignored;

    struct buffer writebuf;
    struct buffer *buf = &writebuf;

    init_buf(buf, strlen(ass) + 1); // with room for terminating '\0'

    char *rp = ass;

    // locate text field in ASS line
    for (int k = 0; k < comma; k++) {
        while (*rp) {
            char tmp = append(sd, buf, rp[0]);
            rp++;
            if (tmp == ',')
                break;
        }
    }
    if (!*rp) {
        talloc_free(buf->string);
        MP_VERBOSE(sd, "SDH filtering not possible - cannot find text field\n");
        return length ? ass : talloc_strdup(NULL, ass);
    }

    bool contains_text = false;  // true if non SDH text was found
    bool line_with_text = false; // if last line contained text
    int wp_line_start = buf->pos; // write pos to start of last line
    int wp_line_end   = buf->pos; // write pos to end of previous line with text (\N)

    // go through the lines in the text
    // they are separated by \N
    while (*rp) {
        line_with_text = false;
        wp_line_start = buf->pos;

        // skip any speaker label
        skip_speaker_label(sd, &rp, buf);

        // go through the rest of the line looking for SDH in () or []
        while (*rp && !(rp[0] == '\\' && rp[1] == 'N')) {
            copy_ass(sd, &rp, buf);
            if (rp[0] == '[') {
                if (!skip_bracketed(sd, &rp, buf)) {
                    append(sd, buf, rp[0]);
                    rp++;
                    line_with_text =  true;
                }
            } else if (rp[0] == '(') {
                if (!skip_parenthesed(sd, &rp, buf)) {
                    append(sd, buf, rp[0]);
                    rp++;
                    line_with_text =  true;
                }
            } else if (*rp && rp[0] != '\\') {
                if ((rp[0] > 32 && rp[0] < 127 && rp[0] != '-') ||
                    (unsigned char)rp[0] >= 0xC0)
                {
                    line_with_text =  true;
                }
                append(sd, buf, rp[0]);
                rp++;
            } else if (rp[0] == '\\' && rp[1] != 'N') {
                append(sd, buf, rp[0]);
                rp++;
            }
        }
        // either end of data or ASS line end defined by separating \N
        if (*rp) {
            // ASS line end
            if (line_with_text) {
                contains_text = true;
                wp_line_end = buf->pos;
                append(sd, buf, rp[0]); // copy backslash
                append(sd, buf, rp[1]); // copy N
                rp += 2; // move read pointer past \N
            } else {
                // no text in line, remove leading hyphen and spaces
                remove_leading_hyphen_space(sd, wp_line_start, buf);
                // and join with next line
                rp += 2; // move read pointer past \N
            }
        }
    }
    // if no normal text i last line - remove last line
    // by moving write pointer to start of last line
    if (!line_with_text) {
        buf->pos = wp_line_end;
    } else {
        contains_text = true;
    }
    if (length)
        talloc_free(ass);
    if (contains_text) {
        // the ASS data contained normal text after filtering
        append(sd, buf, '\0'); // '\0' terminate
        return buf->string;
    } else {
        // all data removed by filtering
        talloc_free(buf->string);
        return NULL;
    }
}