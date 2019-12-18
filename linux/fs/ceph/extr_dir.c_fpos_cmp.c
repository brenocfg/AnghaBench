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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ceph_frag_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpos_frag (int /*<<< orphan*/ ) ; 
 scalar_t__ fpos_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fpos_cmp(loff_t l, loff_t r)
{
	int v = ceph_frag_compare(fpos_frag(l), fpos_frag(r));
	if (v)
		return v;
	return (int)(fpos_off(l) - fpos_off(r));
}