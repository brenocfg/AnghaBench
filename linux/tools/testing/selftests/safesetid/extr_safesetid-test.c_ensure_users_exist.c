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

/* Variables and functions */
 int /*<<< orphan*/  ALLOWED_CHILD1 ; 
 int /*<<< orphan*/  ALLOWED_CHILD2 ; 
 int /*<<< orphan*/  NO_POLICY_USER ; 
 int /*<<< orphan*/  RESTRICTED_PARENT ; 
 int /*<<< orphan*/  ROOT_USER ; 
 int /*<<< orphan*/  ensure_user_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ensure_users_exist(void)
{
	ensure_user_exists(ROOT_USER);
	ensure_user_exists(RESTRICTED_PARENT);
	ensure_user_exists(ALLOWED_CHILD1);
	ensure_user_exists(ALLOWED_CHILD2);
	ensure_user_exists(NO_POLICY_USER);
}