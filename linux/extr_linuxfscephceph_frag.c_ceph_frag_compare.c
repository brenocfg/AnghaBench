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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 unsigned int ceph_frag_bits (int /*<<< orphan*/ ) ; 
 unsigned int ceph_frag_value (int /*<<< orphan*/ ) ; 

int ceph_frag_compare(__u32 a, __u32 b)
{
	unsigned va = ceph_frag_value(a);
	unsigned vb = ceph_frag_value(b);
	if (va < vb)
		return -1;
	if (va > vb)
		return 1;
	va = ceph_frag_bits(a);
	vb = ceph_frag_bits(b);
	if (va < vb)
		return -1;
	if (va > vb)
		return 1;
	return 0;
}