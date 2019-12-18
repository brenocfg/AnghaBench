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
struct TYPE_4__ {int bits; } ;
typedef  TYPE_1__ Bitbuf ;

/* Variables and functions */
 scalar_t__ bitget (TYPE_1__*,int) ; 

__attribute__((used)) static int bitnum (Bitbuf *bb, int n, int c) {
	int i, ret = 0;
	if (n<bb->bits)
		for (i=0; i<c; i++)
			if (bitget (bb, n+i)>0)
				ret |= (1<<(c-i-1));
	return ret;
}