#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_crypt_info; } ;
struct fscrypt_master_key {int /*<<< orphan*/  mk_secret; } ;
struct fscrypt_info {TYPE_2__* ci_master_key; } ;
struct TYPE_3__ {struct fscrypt_master_key** data; } ;
struct TYPE_4__ {TYPE_1__ payload; } ;

/* Variables and functions */
 struct fscrypt_info* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_master_key_secret_present (int /*<<< orphan*/ *) ; 

int fscrypt_drop_inode(struct inode *inode)
{
	const struct fscrypt_info *ci = READ_ONCE(inode->i_crypt_info);
	const struct fscrypt_master_key *mk;

	/*
	 * If ci is NULL, then the inode doesn't have an encryption key set up
	 * so it's irrelevant.  If ci_master_key is NULL, then the master key
	 * was provided via the legacy mechanism of the process-subscribed
	 * keyrings, so we don't know whether it's been removed or not.
	 */
	if (!ci || !ci->ci_master_key)
		return 0;
	mk = ci->ci_master_key->payload.data[0];

	/*
	 * Note: since we aren't holding ->mk_secret_sem, the result here can
	 * immediately become outdated.  But there's no correctness problem with
	 * unnecessarily evicting.  Nor is there a correctness problem with not
	 * evicting while iput() is racing with the key being removed, since
	 * then the thread removing the key will either evict the inode itself
	 * or will correctly detect that it wasn't evicted due to the race.
	 */
	return !is_master_key_secret_present(&mk->mk_secret);
}