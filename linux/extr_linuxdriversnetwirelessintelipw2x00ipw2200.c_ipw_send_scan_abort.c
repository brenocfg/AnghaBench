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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_CMD_SCAN_ABORT ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int ipw_send_cmd_simple (struct ipw_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw_send_scan_abort(struct ipw_priv *priv)
{
	if (!priv) {
		IPW_ERROR("Invalid args\n");
		return -1;
	}

	return ipw_send_cmd_simple(priv, IPW_CMD_SCAN_ABORT);
}