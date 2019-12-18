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
typedef  scalar_t__ u32 ;
struct qstr {scalar_t__ len; unsigned char* name; int /*<<< orphan*/  hash; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {scalar_t__ s_namelen; } ;

/* Variables and functions */
 TYPE_1__* ADFS_SB (int /*<<< orphan*/ ) ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  adfs_tolower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 unsigned long init_name_hash (struct dentry const*) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int
adfs_hash(const struct dentry *parent, struct qstr *qstr)
{
	const unsigned char *name;
	unsigned long hash;
	u32 len;

	if (qstr->len > ADFS_SB(parent->d_sb)->s_namelen)
		return -ENAMETOOLONG;

	len = qstr->len;
	name = qstr->name;
	hash = init_name_hash(parent);
	while (len--)
		hash = partial_name_hash(adfs_tolower(*name++), hash);
	qstr->hash = end_name_hash(hash);

	return 0;
}