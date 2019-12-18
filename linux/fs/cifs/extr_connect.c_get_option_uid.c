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
typedef  int /*<<< orphan*/  substring_t ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int get_option_ul (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_option_uid(substring_t args[], kuid_t *result)
{
	unsigned long value;
	kuid_t uid;
	int rc;

	rc = get_option_ul(args, &value);
	if (rc)
		return rc;

	uid = make_kuid(current_user_ns(), value);
	if (!uid_valid(uid))
		return -EINVAL;

	*result = uid;
	return 0;
}