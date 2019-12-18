#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nilfs_direct_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ u_data; } ;
struct nilfs_bmap {TYPE_1__ b_u; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */

__attribute__((used)) static inline __le64 *nilfs_direct_dptrs(const struct nilfs_bmap *direct)
{
	return (__le64 *)
		((struct nilfs_direct_node *)direct->b_u.u_data + 1);
}