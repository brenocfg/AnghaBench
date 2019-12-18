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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int utf8_mbtowc (int /*<<< orphan*/ *,int const*,int) ; 

int
utf8_mbstowcs(wchar_t *pwcs, const __u8 *s, int n)
{
    __u16 *op;
    const __u8 *ip;
    int size;

    op = pwcs;
    ip = s;
    while (*ip && n > 0) {
        if (*ip & 0x80) {
            size = utf8_mbtowc(op, ip, n);
            if (size == -1) {
                /* Ignore character and move on */
                ip++;
                n--;
            } else {
                op++;
                ip += size;
                n -= size;
            }
        } else {
            *op++ = *ip++;
            n--;
        }
    }
    return (int)(op - pwcs);
}