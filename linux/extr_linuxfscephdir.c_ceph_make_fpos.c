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
typedef  int loff_t ;

/* Variables and functions */
 int HASH_ORDER ; 

loff_t ceph_make_fpos(unsigned high, unsigned off, bool hash_order)
{
	loff_t fpos = ((loff_t)high << 28) | (loff_t)off;
	if (hash_order)
		fpos |= HASH_ORDER;
	return fpos;
}