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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_znode {int child_cnt; TYPE_1__* zbranch; } ;
struct ubifs_info {int dummy; } ;
struct fscrypt_name {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int NAME_GREATER ; 
 int NAME_LESS ; 
 int NAME_MATCHES ; 
 scalar_t__ keys_cmp (struct ubifs_info*,int /*<<< orphan*/ *,union ubifs_key const*) ; 
 int matches_name (struct ubifs_info*,TYPE_1__*,struct fscrypt_name const*) ; 
 int tnc_next (struct ubifs_info*,struct ubifs_znode**,int*) ; 
 int tnc_prev (struct ubifs_info*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int resolve_collision(struct ubifs_info *c, const union ubifs_key *key,
			     struct ubifs_znode **zn, int *n,
			     const struct fscrypt_name *nm)
{
	int err;

	err = matches_name(c, &(*zn)->zbranch[*n], nm);
	if (unlikely(err < 0))
		return err;
	if (err == NAME_MATCHES)
		return 1;

	if (err == NAME_GREATER) {
		/* Look left */
		while (1) {
			err = tnc_prev(c, zn, n);
			if (err == -ENOENT) {
				ubifs_assert(c, *n == 0);
				*n = -1;
				return 0;
			}
			if (err < 0)
				return err;
			if (keys_cmp(c, &(*zn)->zbranch[*n].key, key)) {
				/*
				 * We have found the branch after which we would
				 * like to insert, but inserting in this znode
				 * may still be wrong. Consider the following 3
				 * znodes, in the case where we are resolving a
				 * collision with Key2.
				 *
				 *                  znode zp
				 *            ----------------------
				 * level 1     |  Key0  |  Key1  |
				 *            -----------------------
				 *                 |            |
				 *       znode za  |            |  znode zb
				 *          ------------      ------------
				 * level 0  |  Key0  |        |  Key2  |
				 *          ------------      ------------
				 *
				 * The lookup finds Key2 in znode zb. Lets say
				 * there is no match and the name is greater so
				 * we look left. When we find Key0, we end up
				 * here. If we return now, we will insert into
				 * znode za at slot n = 1.  But that is invalid
				 * according to the parent's keys.  Key2 must
				 * be inserted into znode zb.
				 *
				 * Note, this problem is not relevant for the
				 * case when we go right, because
				 * 'tnc_insert()' would correct the parent key.
				 */
				if (*n == (*zn)->child_cnt - 1) {
					err = tnc_next(c, zn, n);
					if (err) {
						/* Should be impossible */
						ubifs_assert(c, 0);
						if (err == -ENOENT)
							err = -EINVAL;
						return err;
					}
					ubifs_assert(c, *n == 0);
					*n = -1;
				}
				return 0;
			}
			err = matches_name(c, &(*zn)->zbranch[*n], nm);
			if (err < 0)
				return err;
			if (err == NAME_LESS)
				return 0;
			if (err == NAME_MATCHES)
				return 1;
			ubifs_assert(c, err == NAME_GREATER);
		}
	} else {
		int nn = *n;
		struct ubifs_znode *znode = *zn;

		/* Look right */
		while (1) {
			err = tnc_next(c, &znode, &nn);
			if (err == -ENOENT)
				return 0;
			if (err < 0)
				return err;
			if (keys_cmp(c, &znode->zbranch[nn].key, key))
				return 0;
			err = matches_name(c, &znode->zbranch[nn], nm);
			if (err < 0)
				return err;
			if (err == NAME_GREATER)
				return 0;
			*zn = znode;
			*n = nn;
			if (err == NAME_MATCHES)
				return 1;
			ubifs_assert(c, err == NAME_LESS);
		}
	}
}