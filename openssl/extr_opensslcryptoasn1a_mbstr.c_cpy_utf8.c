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

/* Variables and functions */
 int UTF8_putc (unsigned char*,int,unsigned long) ; 

__attribute__((used)) static int cpy_utf8(unsigned long value, void *arg)
{
    unsigned char **p;
    int ret;
    p = arg;
    /* We already know there is enough room so pass 0xff as the length */
    ret = UTF8_putc(*p, 0xff, value);
    *p += ret;
    return 1;
}