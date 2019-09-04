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
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ DELTA ; 

__attribute__((used)) static void TEA_transform(unsigned int buf[4], unsigned int const in[])
{
	__u32 sum = 0;
	__u32 b0 = buf[0], b1 = buf[1];
	__u32 a = in[0], b = in[1], c = in[2], d = in[3];
	int n = 16;

	do {
		sum += DELTA;
		b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);
		b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);
	} while (--n);

	buf[0] += b0;
	buf[1] += b1;
}