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
typedef  int /*<<< orphan*/  u8 ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int UBIFS_HASH_ARR_SZ ; 
 int __ubifs_node_calc_hash (struct ubifs_info const*,void const*,int /*<<< orphan*/ *) ; 
 scalar_t__ ubifs_check_hash (struct ubifs_info const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int __ubifs_node_check_hash(const struct ubifs_info *c, const void *node,
			    const u8 *expected)
{
	u8 calc[UBIFS_HASH_ARR_SZ];
	int err;

	err = __ubifs_node_calc_hash(c, node, calc);
	if (err)
		return err;

	if (ubifs_check_hash(c, expected, calc))
		return -EPERM;

	return 0;
}