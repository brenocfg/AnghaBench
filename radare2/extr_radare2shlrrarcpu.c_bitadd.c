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

__attribute__((used)) static void bitadd(Bitbuf *bb, unsigned int v, int n) {
	int i, b, bit;
	for (i=0; i<n; i++, bb->bits++) {
		b = (bb->bits+i)/8;
		bit = (bb->bits+i)%8;
//printf ("[%d].%d = %d\n", b, bit, v& (1<<(n-i-1)));
		if (!bit) bb->out[b] = 0;
//printf ("BIT (%d)\n", n-i-1);
		//if (v&(1<<(n-i-1))) bb->out[b] |= 1<<bit;
		if (v&(1<<(n-i-1))) bb->out[b] |= 1<<bit;
	//	printf ("%d", oz);
	}
	//printf ("\n");
}