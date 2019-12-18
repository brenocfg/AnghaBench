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
struct fscrypt_master_key_secret {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
is_master_key_secret_present(const struct fscrypt_master_key_secret *secret)
{
	/*
	 * The READ_ONCE() is only necessary for fscrypt_drop_inode() and
	 * fscrypt_key_describe().  These run in atomic context, so they can't
	 * take ->mk_secret_sem and thus 'secret' can change concurrently which
	 * would be a data race.  But they only need to know whether the secret
	 * *was* present at the time of check, so READ_ONCE() suffices.
	 */
	return READ_ONCE(secret->size) != 0;
}