#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* buffer; size_t len; } ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_need_bytes (TYPE_1__*,int) ; 
 char* print_number_llu_r (char*,unsigned long long) ; 
 char* print_number_lu_r (char*,unsigned long long) ; 

void buffer_print_llu(BUFFER *wb, unsigned long long uvalue)
{
    buffer_need_bytes(wb, 50);

    char *str = &wb->buffer[wb->len];
    char *wstr = str;

#ifdef ENVIRONMENT32
    if(uvalue > (unsigned long long)0xffffffff)
        wstr = print_number_llu_r(wstr, uvalue);
    else
        wstr = print_number_lu_r(wstr, uvalue);
#else
    do *wstr++ = (char)('0' + (uvalue % 10)); while(uvalue /= 10);
#endif

    // terminate it
    *wstr = '\0';

    // reverse it
    char *begin = str, *end = wstr - 1, aux;
    while (end > begin) aux = *end, *end-- = *begin, *begin++ = aux;

    // return the buffer length
    wb->len += wstr - str;
}