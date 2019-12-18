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
typedef  scalar_t__ cap_flag_value_t ;

/* Variables and functions */
 scalar_t__ CAP_CLEAR ; 
 int /*<<< orphan*/  CAP_EFFECTIVE ; 
 int /*<<< orphan*/  CAP_IS_SUPPORTED (int /*<<< orphan*/ ) ; 
 scalar_t__ CAP_SET ; 
 int /*<<< orphan*/  CAP_SETFCAP ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ cap_free (int /*<<< orphan*/ ) ; 
 scalar_t__ cap_get_flag (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  cap_get_proc () ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static bool is_admin(void)
{
	cap_t caps;
	cap_flag_value_t sysadmin = CAP_CLEAR;
	const cap_value_t cap_val = CAP_SYS_ADMIN;

#ifdef CAP_IS_SUPPORTED
	if (!CAP_IS_SUPPORTED(CAP_SETFCAP)) {
		perror("cap_get_flag");
		return false;
	}
#endif
	caps = cap_get_proc();
	if (!caps) {
		perror("cap_get_proc");
		return false;
	}
	if (cap_get_flag(caps, cap_val, CAP_EFFECTIVE, &sysadmin))
		perror("cap_get_flag");
	if (cap_free(caps))
		perror("cap_free");
	return (sysadmin == CAP_SET);
}