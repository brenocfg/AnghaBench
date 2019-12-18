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
struct target {char* uid_str; int /*<<< orphan*/  uid; } ;
struct passwd {int /*<<< orphan*/  pw_uid; } ;
typedef  enum target_errno { ____Placeholder_target_errno } target_errno ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int TARGET_ERRNO__INVALID_UID ; 
 int TARGET_ERRNO__SUCCESS ; 
 int TARGET_ERRNO__USER_NOT_FOUND ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  getpwnam_r (char const*,struct passwd*,char*,int,struct passwd**) ; 
 int /*<<< orphan*/  getpwuid_r (int,struct passwd*,char*,int,struct passwd**) ; 
 int strtol (char const*,char**,int) ; 

enum target_errno target__parse_uid(struct target *target)
{
	struct passwd pwd, *result;
	char buf[1024];
	const char *str = target->uid_str;

	target->uid = UINT_MAX;
	if (str == NULL)
		return TARGET_ERRNO__SUCCESS;

	/* Try user name first */
	getpwnam_r(str, &pwd, buf, sizeof(buf), &result);

	if (result == NULL) {
		/*
		 * The user name not found. Maybe it's a UID number.
		 */
		char *endptr;
		int uid = strtol(str, &endptr, 10);

		if (*endptr != '\0')
			return TARGET_ERRNO__INVALID_UID;

		getpwuid_r(uid, &pwd, buf, sizeof(buf), &result);

		if (result == NULL)
			return TARGET_ERRNO__USER_NOT_FOUND;
	}

	target->uid = result->pw_uid;
	return TARGET_ERRNO__SUCCESS;
}