#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_27__ {void* contenttype; } ;
struct TYPE_26__ {int result_options; int /*<<< orphan*/  before; } ;
struct TYPE_25__ {int /*<<< orphan*/  last_accessed_time; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDR ;
typedef  TYPE_3__ BUFFER ;

/* Variables and functions */
 void* CT_APPLICATION_JSON ; 
 void* CT_APPLICATION_X_JAVASCRIPT ; 
 void* CT_TEXT_HTML ; 
 void* CT_TEXT_PLAIN ; 
#define  DATASOURCE_CSV 139 
#define  DATASOURCE_CSV_JSON_ARRAY 138 
#define  DATASOURCE_CSV_MARKDOWN 137 
#define  DATASOURCE_DATATABLE_JSON 136 
#define  DATASOURCE_DATATABLE_JSONP 135 
#define  DATASOURCE_HTML 134 
#define  DATASOURCE_JSON 133 
#define  DATASOURCE_JSONP 132 
#define  DATASOURCE_JS_ARRAY 131 
#define  DATASOURCE_SSV 130 
#define  DATASOURCE_SSV_COMMA 129 
#define  DATASOURCE_TSV 128 
 int HTTP_RESP_INTERNAL_SERVER_ERROR ; 
 int HTTP_RESP_OK ; 
 int RRDR_OPTION_JSON_WRAP ; 
 int RRDR_OPTION_LABEL_QUOTES ; 
 int RRDR_RESULT_OPTION_ABSOLUTE ; 
 int RRDR_RESULT_OPTION_RELATIVE ; 
 int /*<<< orphan*/  buffer_cacheable (TYPE_3__*) ; 
 int /*<<< orphan*/  buffer_no_cacheable (TYPE_3__*) ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * buffer_tostring (TYPE_3__*) ; 
 int /*<<< orphan*/  now_realtime_sec () ; 
 TYPE_2__* rrd2rrdr (TYPE_1__*,long,long long,long long,int,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdr2csv (TYPE_2__*,TYPE_3__*,int,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  rrdr2json (TYPE_2__*,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  rrdr2ssv (TYPE_2__*,TYPE_3__*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  rrdr_free (TYPE_2__*) ; 
 int /*<<< orphan*/  rrdr_json_wrapper_begin (TYPE_2__*,TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  rrdr_json_wrapper_end (TYPE_2__*,TYPE_3__*,int,int,int) ; 
 scalar_t__ rrdr_rows (TYPE_2__*) ; 

int rrdset2anything_api_v1(
          RRDSET *st
        , BUFFER *wb
        , BUFFER *dimensions
        , uint32_t format
        , long points
        , long long after
        , long long before
        , int group_method
        , long group_time
        , uint32_t options
        , time_t *latest_timestamp
) {
    st->last_accessed_time = now_realtime_sec();

    RRDR *r = rrd2rrdr(st, points, after, before, group_method, group_time, options, dimensions?buffer_tostring(dimensions):NULL);
    if(!r) {
        buffer_strcat(wb, "Cannot generate output with these parameters on this chart.");
        return HTTP_RESP_INTERNAL_SERVER_ERROR;
    }

    if(r->result_options & RRDR_RESULT_OPTION_RELATIVE)
        buffer_no_cacheable(wb);
    else if(r->result_options & RRDR_RESULT_OPTION_ABSOLUTE)
        buffer_cacheable(wb);

    if(latest_timestamp && rrdr_rows(r) > 0)
        *latest_timestamp = r->before;

    switch(format) {
    case DATASOURCE_SSV:
        if(options & RRDR_OPTION_JSON_WRAP) {
            wb->contenttype = CT_APPLICATION_JSON;
            rrdr_json_wrapper_begin(r, wb, format, options, 1);
            rrdr2ssv(r, wb, options, "", " ", "");
            rrdr_json_wrapper_end(r, wb, format, options, 1);
        }
        else {
            wb->contenttype = CT_TEXT_PLAIN;
            rrdr2ssv(r, wb, options, "", " ", "");
        }
        break;

    case DATASOURCE_SSV_COMMA:
        if(options & RRDR_OPTION_JSON_WRAP) {
            wb->contenttype = CT_APPLICATION_JSON;
            rrdr_json_wrapper_begin(r, wb, format, options, 1);
            rrdr2ssv(r, wb, options, "", ",", "");
            rrdr_json_wrapper_end(r, wb, format, options, 1);
        }
        else {
            wb->contenttype = CT_TEXT_PLAIN;
            rrdr2ssv(r, wb, options, "", ",", "");
        }
        break;

    case DATASOURCE_JS_ARRAY:
        if(options & RRDR_OPTION_JSON_WRAP) {
            wb->contenttype = CT_APPLICATION_JSON;
            rrdr_json_wrapper_begin(r, wb, format, options, 0);
            rrdr2ssv(r, wb, options, "[", ",", "]");
            rrdr_json_wrapper_end(r, wb, format, options, 0);
        }
        else {
            wb->contenttype = CT_APPLICATION_JSON;
            rrdr2ssv(r, wb, options, "[", ",", "]");
        }
        break;

    case DATASOURCE_CSV:
        if(options & RRDR_OPTION_JSON_WRAP) {
            wb->contenttype = CT_APPLICATION_JSON;
            rrdr_json_wrapper_begin(r, wb, format, options, 1);
            rrdr2csv(r, wb, format, options, "", ",", "\\n", "");
            rrdr_json_wrapper_end(r, wb, format, options, 1);
        }
        else {
            wb->contenttype = CT_TEXT_PLAIN;
            rrdr2csv(r, wb, format, options, "", ",", "\r\n", "");
        }
        break;

    case DATASOURCE_CSV_MARKDOWN:
        if(options & RRDR_OPTION_JSON_WRAP) {
            wb->contenttype = CT_APPLICATION_JSON;
            rrdr_json_wrapper_begin(r, wb, format, options, 1);
            rrdr2csv(r, wb, format, options, "", "|", "\\n", "");
            rrdr_json_wrapper_end(r, wb, format, options, 1);
        }
        else {
            wb->contenttype = CT_TEXT_PLAIN;
            rrdr2csv(r, wb, format, options, "", "|", "\r\n", "");
        }
        break;

    case DATASOURCE_CSV_JSON_ARRAY:
        wb->contenttype = CT_APPLICATION_JSON;
        if(options & RRDR_OPTION_JSON_WRAP) {
            rrdr_json_wrapper_begin(r, wb, format, options, 0);
            buffer_strcat(wb, "[\n");
            rrdr2csv(r, wb, format, options + RRDR_OPTION_LABEL_QUOTES, "[", ",", "]", ",\n");
            buffer_strcat(wb, "\n]");
            rrdr_json_wrapper_end(r, wb, format, options, 0);
        }
        else {
            wb->contenttype = CT_APPLICATION_JSON;
            buffer_strcat(wb, "[\n");
            rrdr2csv(r, wb, format, options + RRDR_OPTION_LABEL_QUOTES, "[", ",", "]", ",\n");
            buffer_strcat(wb, "\n]");
        }
        break;

    case DATASOURCE_TSV:
        if(options & RRDR_OPTION_JSON_WRAP) {
            wb->contenttype = CT_APPLICATION_JSON;
            rrdr_json_wrapper_begin(r, wb, format, options, 1);
            rrdr2csv(r, wb, format, options, "", "\t", "\\n", "");
            rrdr_json_wrapper_end(r, wb, format, options, 1);
        }
        else {
            wb->contenttype = CT_TEXT_PLAIN;
            rrdr2csv(r, wb, format, options, "", "\t", "\r\n", "");
        }
        break;

    case DATASOURCE_HTML:
        if(options & RRDR_OPTION_JSON_WRAP) {
            wb->contenttype = CT_APPLICATION_JSON;
            rrdr_json_wrapper_begin(r, wb, format, options, 1);
            buffer_strcat(wb, "<html>\\n<center>\\n<table border=\\\"0\\\" cellpadding=\\\"5\\\" cellspacing=\\\"5\\\">\\n");
            rrdr2csv(r, wb, format, options, "<tr><td>", "</td><td>", "</td></tr>\\n", "");
            buffer_strcat(wb, "</table>\\n</center>\\n</html>\\n");
            rrdr_json_wrapper_end(r, wb, format, options, 1);
        }
        else {
            wb->contenttype = CT_TEXT_HTML;
            buffer_strcat(wb, "<html>\n<center>\n<table border=\"0\" cellpadding=\"5\" cellspacing=\"5\">\n");
            rrdr2csv(r, wb, format, options, "<tr><td>", "</td><td>", "</td></tr>\n", "");
            buffer_strcat(wb, "</table>\n</center>\n</html>\n");
        }
        break;

    case DATASOURCE_DATATABLE_JSONP:
        wb->contenttype = CT_APPLICATION_X_JAVASCRIPT;

        if(options & RRDR_OPTION_JSON_WRAP)
            rrdr_json_wrapper_begin(r, wb, format, options, 0);

        rrdr2json(r, wb, options, 1);

        if(options & RRDR_OPTION_JSON_WRAP)
            rrdr_json_wrapper_end(r, wb, format, options, 0);
        break;

    case DATASOURCE_DATATABLE_JSON:
        wb->contenttype = CT_APPLICATION_JSON;

        if(options & RRDR_OPTION_JSON_WRAP)
            rrdr_json_wrapper_begin(r, wb, format, options, 0);

        rrdr2json(r, wb, options, 1);

        if(options & RRDR_OPTION_JSON_WRAP)
            rrdr_json_wrapper_end(r, wb, format, options, 0);
        break;

    case DATASOURCE_JSONP:
        wb->contenttype = CT_APPLICATION_X_JAVASCRIPT;
        if(options & RRDR_OPTION_JSON_WRAP)
            rrdr_json_wrapper_begin(r, wb, format, options, 0);

        rrdr2json(r, wb, options, 0);

        if(options & RRDR_OPTION_JSON_WRAP)
            rrdr_json_wrapper_end(r, wb, format, options, 0);
        break;

    case DATASOURCE_JSON:
    default:
        wb->contenttype = CT_APPLICATION_JSON;

        if(options & RRDR_OPTION_JSON_WRAP)
            rrdr_json_wrapper_begin(r, wb, format, options, 0);

        rrdr2json(r, wb, options, 0);

        if(options & RRDR_OPTION_JSON_WRAP)
            rrdr_json_wrapper_end(r, wb, format, options, 0);
        break;
    }

    rrdr_free(r);
    return HTTP_RESP_OK;
}