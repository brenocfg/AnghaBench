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
typedef  int u64 ;
struct auth_cred {int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hash_64 (int,unsigned int) ; 
 int /*<<< orphan*/  init_user_ns ; 

__attribute__((used)) static int
unx_hash_cred(struct auth_cred *acred, unsigned int hashbits)
{
	return hash_64(from_kgid(&init_user_ns, acred->gid) |
		((u64)from_kuid(&init_user_ns, acred->uid) <<
			(sizeof(gid_t) * 8)), hashbits);
}