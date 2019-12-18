#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bits; int* out; } ;
typedef  TYPE_1__ Bitbuf ;

/* Variables and functions */

__attribute__((used)) static int bitget(Bitbuf *bb, int bit) {
	if (bit>=bb->bits) return -1;
	return (bb->out[bit/8] & (1<<((bit%8))))? 1: 0;
}