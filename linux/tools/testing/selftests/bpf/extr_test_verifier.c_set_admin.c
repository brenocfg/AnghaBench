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
typedef  int /*<<< orphan*/  cap_value_t ;
typedef  int /*<<< orphan*/  cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CLEAR ; 
 int /*<<< orphan*/  CAP_EFFECTIVE ; 
 int /*<<< orphan*/  CAP_SET ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ cap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_get_proc () ; 
 scalar_t__ cap_set_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ cap_set_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int set_admin(bool admin)
{
	cap_t caps;
	const cap_value_t cap_val = CAP_SYS_ADMIN;
	int ret = -1;

	caps = cap_get_proc();
	if (!caps) {
		perror("cap_get_proc");
		return -1;
	}
	if (cap_set_flag(caps, CAP_EFFECTIVE, 1, &cap_val,
				admin ? CAP_SET : CAP_CLEAR)) {
		perror("cap_set_flag");
		goto out;
	}
	if (cap_set_proc(caps)) {
		perror("cap_set_proc");
		goto out;
	}
	ret = 0;
out:
	if (cap_free(caps))
		perror("cap_free");
	return ret;
}