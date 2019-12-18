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
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int get_option_ul (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int get_option_gid(substring_t args[], kgid_t *result)
{
	unsigned long value;
	kgid_t gid;
	int rc;

	rc = get_option_ul(args, &value);
	if (rc)
		return rc;

	gid = make_kgid(current_user_ns(), value);
	if (!gid_valid(gid))
		return -EINVAL;

	*result = gid;
	return 0;
}