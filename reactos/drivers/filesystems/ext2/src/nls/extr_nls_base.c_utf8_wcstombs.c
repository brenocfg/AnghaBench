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
typedef  int wchar_t ;
typedef  scalar_t__ __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int utf8_wctomb (scalar_t__*,int const,int) ; 

int
utf8_wcstombs(__u8 *s, const wchar_t *pwcs, int maxlen)
{
    const __u16 *ip;
    __u8 *op;
    int size;

    op = s;
    ip = pwcs;
    while (*ip && maxlen > 0) {
        if (*ip > 0x7f) {
            size = utf8_wctomb(op, *ip, maxlen);
            if (size == -1) {
                /* Ignore character and move on */
                maxlen--;
            } else {
                op += size;
                maxlen -= size;
            }
        } else {
            *op++ = (__u8) *ip;
        }
        ip++;
    }
    return (int)(op - s);
}