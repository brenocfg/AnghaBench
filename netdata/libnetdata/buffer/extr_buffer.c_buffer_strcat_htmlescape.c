#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* buffer; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_need_bytes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  buffer_overflow_check (TYPE_1__*) ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_1__*,char*) ; 

void buffer_strcat_htmlescape(BUFFER *wb, const char *txt)
{
    while(*txt) {
        switch(*txt) {
            case '&': buffer_strcat(wb, "&amp;"); break;
            case '<': buffer_strcat(wb, "&lt;"); break;
            case '>': buffer_strcat(wb, "&gt;"); break;
            case '"': buffer_strcat(wb, "&quot;"); break;
            case '/': buffer_strcat(wb, "&#x2F;"); break;
            case '\'': buffer_strcat(wb, "&#x27;"); break;
            default: {
                buffer_need_bytes(wb, 1);
                wb->buffer[wb->len++] = *txt;
            }
        }
        txt++;
    }

    buffer_overflow_check(wb);
}