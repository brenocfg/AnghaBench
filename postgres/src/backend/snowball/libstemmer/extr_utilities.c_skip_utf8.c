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
typedef  int symbol ;

/* Variables and functions */

extern int skip_utf8(const symbol * p, int c, int lb, int l, int n) {
    int b;
    if (n >= 0) {
        for (; n > 0; n--) {
            if (c >= l) return -1;
            b = p[c++];
            if (b >= 0xC0) {   /* 1100 0000 */
                while (c < l) {
                    b = p[c];
                    if (b >= 0xC0 || b < 0x80) break;
                    /* break unless b is 10------ */
                    c++;
                }
            }
        }
    } else {
        for (; n < 0; n++) {
            if (c <= lb) return -1;
            b = p[--c];
            if (b >= 0x80) {   /* 1000 0000 */
                while (c > lb) {
                    b = p[c];
                    if (b >= 0xC0) break; /* 1100 0000 */
                    c--;
                }
            }
        }
    }
    return c;
}