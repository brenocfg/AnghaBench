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
struct ceph_pg_pool_info {int pg_num_mask; int pgp_num_mask; scalar_t__ pgp_num; scalar_t__ pg_num; } ;

/* Variables and functions */
 int calc_bits_of (scalar_t__) ; 

__attribute__((used)) static void calc_pg_masks(struct ceph_pg_pool_info *pi)
{
	pi->pg_num_mask = (1 << calc_bits_of(pi->pg_num-1)) - 1;
	pi->pgp_num_mask = (1 << calc_bits_of(pi->pgp_num-1)) - 1;
}