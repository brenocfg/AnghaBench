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
typedef  int /*<<< orphan*/  u8 ;
struct ubifs_info {TYPE_1__* mst_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash_lpt; } ;

/* Variables and functions */
 int EPERM ; 
 int UBIFS_HASH_ARR_SZ ; 
 int /*<<< orphan*/  ubifs_authenticated (struct ubifs_info*) ; 
 scalar_t__ ubifs_check_hash (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*) ; 
 int ubifs_lpt_calc_hash (struct ubifs_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpt_check_hash(struct ubifs_info *c)
{
	int err;
	u8 hash[UBIFS_HASH_ARR_SZ];

	if (!ubifs_authenticated(c))
		return 0;

	err = ubifs_lpt_calc_hash(c, hash);
	if (err)
		return err;

	if (ubifs_check_hash(c, c->mst_node->hash_lpt, hash)) {
		err = -EPERM;
		ubifs_err(c, "Failed to authenticate LPT");
	} else {
		err = 0;
	}

	return err;
}