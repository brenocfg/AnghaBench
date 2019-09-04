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
typedef  int /*<<< orphan*/  calculated_number ;
struct TYPE_6__ {size_t len; char* buffer; } ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_need_bytes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  buffer_overflow_check (TYPE_1__*) ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_1__*,char*) ; 
 scalar_t__ isinf (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 
 scalar_t__ print_calculated_number (char*,int /*<<< orphan*/ ) ; 

void buffer_rrd_value(BUFFER *wb, calculated_number value)
{
    buffer_need_bytes(wb, 50);

    if(isnan(value) || isinf(value)) {
        buffer_strcat(wb, "null");
        return;
    }
    else
        wb->len += print_calculated_number(&wb->buffer[wb->len], value);

    // terminate it
    buffer_need_bytes(wb, 1);
    wb->buffer[wb->len] = '\0';

    buffer_overflow_check(wb);
}