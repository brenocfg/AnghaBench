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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
#define  DATASOURCE_CSV 137 
#define  DATASOURCE_DATATABLE_JSON 136 
#define  DATASOURCE_DATATABLE_JSONP 135 
 char* DATASOURCE_FORMAT_CSV ; 
 char* DATASOURCE_FORMAT_DATATABLE_JSON ; 
 char* DATASOURCE_FORMAT_DATATABLE_JSONP ; 
 char* DATASOURCE_FORMAT_HTML ; 
 char* DATASOURCE_FORMAT_JSON ; 
 char* DATASOURCE_FORMAT_JSONP ; 
 char* DATASOURCE_FORMAT_JS_ARRAY ; 
 char* DATASOURCE_FORMAT_SSV ; 
 char* DATASOURCE_FORMAT_SSV_COMMA ; 
 char* DATASOURCE_FORMAT_TSV ; 
#define  DATASOURCE_HTML 134 
#define  DATASOURCE_JSON 133 
#define  DATASOURCE_JSONP 132 
#define  DATASOURCE_JS_ARRAY 131 
#define  DATASOURCE_SSV 130 
#define  DATASOURCE_SSV_COMMA 129 
#define  DATASOURCE_TSV 128 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 

void rrdr_buffer_print_format(BUFFER *wb, uint32_t format)  {
    switch(format) {
        case DATASOURCE_JSON:
            buffer_strcat(wb, DATASOURCE_FORMAT_JSON);
            break;

        case DATASOURCE_DATATABLE_JSON:
            buffer_strcat(wb, DATASOURCE_FORMAT_DATATABLE_JSON);
            break;

        case DATASOURCE_DATATABLE_JSONP:
            buffer_strcat(wb, DATASOURCE_FORMAT_DATATABLE_JSONP);
            break;

        case DATASOURCE_JSONP:
            buffer_strcat(wb, DATASOURCE_FORMAT_JSONP);
            break;

        case DATASOURCE_SSV:
            buffer_strcat(wb, DATASOURCE_FORMAT_SSV);
            break;

        case DATASOURCE_CSV:
            buffer_strcat(wb, DATASOURCE_FORMAT_CSV);
            break;

        case DATASOURCE_TSV:
            buffer_strcat(wb, DATASOURCE_FORMAT_TSV);
            break;

        case DATASOURCE_HTML:
            buffer_strcat(wb, DATASOURCE_FORMAT_HTML);
            break;

        case DATASOURCE_JS_ARRAY:
            buffer_strcat(wb, DATASOURCE_FORMAT_JS_ARRAY);
            break;

        case DATASOURCE_SSV_COMMA:
            buffer_strcat(wb, DATASOURCE_FORMAT_SSV_COMMA);
            break;

        default:
            buffer_strcat(wb, "unknown");
            break;
    }
}