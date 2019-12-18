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
struct SN_env {size_t c; size_t l; int* p; } ;

/* Variables and functions */

extern int in_grouping(struct SN_env * z, const unsigned char * s, int min, int max, int repeat) {
    do {
	int ch;
	if (z->c >= z->l) return -1;
	ch = z->p[z->c];
	if (ch > max || (ch -= min) < 0 || (s[ch >> 3] & (0X1 << (ch & 0X7))) == 0)
	    return 1;
	z->c++;
    } while (repeat);
    return 0;
}