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
struct SN_env {int c; int /*<<< orphan*/  l; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int get_utf8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

extern int out_grouping_U(struct SN_env * z, const unsigned char * s, int min, int max, int repeat) {
    do {
	int ch;
	int w = get_utf8(z->p, z->c, z->l, & ch);
	if (!w) return -1;
	if (!(ch > max || (ch -= min) < 0 || (s[ch >> 3] & (0X1 << (ch & 0X7))) == 0))
	    return w;
	z->c += w;
    } while (repeat);
    return 0;
}