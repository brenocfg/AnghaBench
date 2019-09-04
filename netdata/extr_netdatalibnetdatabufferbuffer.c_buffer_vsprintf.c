#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {int size; int len; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_need_bytes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  buffer_overflow_check (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vsnprintfz (int /*<<< orphan*/ *,size_t,char const*,int /*<<< orphan*/ ) ; 

void buffer_vsprintf(BUFFER *wb, const char *fmt, va_list args)
{
    if(unlikely(!fmt || !*fmt)) return;

    buffer_need_bytes(wb, 2);

    size_t len = wb->size - wb->len - 1;

    wb->len += vsnprintfz(&wb->buffer[wb->len], len, fmt, args);

    buffer_overflow_check(wb);

    // the buffer is \0 terminated by vsnprintfz
}