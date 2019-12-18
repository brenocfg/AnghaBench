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
typedef  int /*<<< orphan*/  u32 ;
struct smack_known {int /*<<< orphan*/  smk_secid; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smack_cred (struct cred const*) ; 
 struct smack_known* smk_of_task (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smack_cred_getsecid(const struct cred *cred, u32 *secid)
{
	struct smack_known *skp;

	rcu_read_lock();
	skp = smk_of_task(smack_cred(cred));
	*secid = skp->smk_secid;
	rcu_read_unlock();
}