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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ v1; } ;
struct fscrypt_info {TYPE_2__ ci_policy; } ;

/* Variables and functions */
 int FSCRYPT_POLICY_FLAG_DIRECT_KEY ; 
 int setup_v1_file_key_derived (struct fscrypt_info*,int /*<<< orphan*/  const*) ; 
 int setup_v1_file_key_direct (struct fscrypt_info*,int /*<<< orphan*/  const*) ; 

int fscrypt_setup_v1_file_key(struct fscrypt_info *ci, const u8 *raw_master_key)
{
	if (ci->ci_policy.v1.flags & FSCRYPT_POLICY_FLAG_DIRECT_KEY)
		return setup_v1_file_key_direct(ci, raw_master_key);
	else
		return setup_v1_file_key_derived(ci, raw_master_key);
}