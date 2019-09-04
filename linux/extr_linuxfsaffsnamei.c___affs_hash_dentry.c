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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  (* toupper_t ) (int /*<<< orphan*/  const) ;
struct qstr {int /*<<< orphan*/  hash; int /*<<< orphan*/  len; int /*<<< orphan*/ * name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFFSNAMEMAX ; 
 int affs_check_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 unsigned long init_name_hash (struct dentry const*) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline int
__affs_hash_dentry(const struct dentry *dentry, struct qstr *qstr, toupper_t toupper, bool notruncate)
{
	const u8 *name = qstr->name;
	unsigned long hash;
	int retval;
	u32 len;

	retval = affs_check_name(qstr->name, qstr->len, notruncate);
	if (retval)
		return retval;

	hash = init_name_hash(dentry);
	len = min(qstr->len, AFFSNAMEMAX);
	for (; len > 0; name++, len--)
		hash = partial_name_hash(toupper(*name), hash);
	qstr->hash = end_name_hash(hash);

	return 0;
}