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
struct s35390a {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S35390A_CMD_STATUS1 ; 
 char S35390A_FLAG_BLD ; 
 char S35390A_FLAG_POC ; 
 int /*<<< orphan*/  msleep (int) ; 
 int s35390a_get_reg (struct s35390a*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int s35390a_read_status(struct s35390a *s35390a, char *status1)
{
	int ret;

	ret = s35390a_get_reg(s35390a, S35390A_CMD_STATUS1, status1, 1);
	if (ret < 0)
		return ret;

	if (*status1 & S35390A_FLAG_POC) {
		/*
		 * Do not communicate for 0.5 seconds since the power-on
		 * detection circuit is in operation.
		 */
		msleep(500);
		return 1;
	} else if (*status1 & S35390A_FLAG_BLD)
		return 1;
	/*
	 * If both POC and BLD are unset everything is fine.
	 */
	return 0;
}