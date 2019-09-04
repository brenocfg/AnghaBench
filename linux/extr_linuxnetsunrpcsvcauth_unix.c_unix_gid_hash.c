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
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GID_HASHBITS ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hash_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 

__attribute__((used)) static int unix_gid_hash(kuid_t uid)
{
	return hash_long(from_kuid(&init_user_ns, uid), GID_HASHBITS);
}