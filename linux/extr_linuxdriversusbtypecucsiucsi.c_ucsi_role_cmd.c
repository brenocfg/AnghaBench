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
struct ucsi_control {int dummy; } ;
struct ucsi_connector {int /*<<< orphan*/  ucsi; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  UCSI_CMD_SET_NTFY_ENABLE (struct ucsi_control,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCSI_ENABLE_NTFY_ALL ; 
 int /*<<< orphan*/  ucsi_reset_connector (struct ucsi_connector*,int) ; 
 int /*<<< orphan*/  ucsi_reset_ppm (int /*<<< orphan*/ ) ; 
 int ucsi_run_command (int /*<<< orphan*/ ,struct ucsi_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucsi_role_cmd(struct ucsi_connector *con, struct ucsi_control *ctrl)
{
	int ret;

	ret = ucsi_run_command(con->ucsi, ctrl, NULL, 0);
	if (ret == -ETIMEDOUT) {
		struct ucsi_control c;

		/* PPM most likely stopped responding. Resetting everything. */
		ucsi_reset_ppm(con->ucsi);

		UCSI_CMD_SET_NTFY_ENABLE(c, UCSI_ENABLE_NTFY_ALL);
		ucsi_run_command(con->ucsi, &c, NULL, 0);

		ucsi_reset_connector(con, true);
	}

	return ret;
}