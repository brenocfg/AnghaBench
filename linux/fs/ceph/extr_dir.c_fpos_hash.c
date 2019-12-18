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
 int ceph_frag_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpos_frag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned fpos_hash(loff_t p)
{
	return ceph_frag_value(fpos_frag(p));
}