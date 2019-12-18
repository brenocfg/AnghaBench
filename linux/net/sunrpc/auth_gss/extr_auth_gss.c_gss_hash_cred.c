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
struct auth_cred {TYPE_1__* cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  fsuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hash_64 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  init_user_ns ; 

__attribute__((used)) static int
gss_hash_cred(struct auth_cred *acred, unsigned int hashbits)
{
	return hash_64(from_kuid(&init_user_ns, acred->cred->fsuid), hashbits);
}