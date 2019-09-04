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
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,int) ; 
 int /*<<< orphan*/  IPW_DEBUG_TRACE (char*) ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int /*<<< orphan*/  IPW_RESET_REG ; 
 int /*<<< orphan*/  IPW_RESET_REG_MASTER_DISABLED ; 
 int /*<<< orphan*/  IPW_RESET_REG_STOP_MASTER ; 
 int ipw_poll_bit (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipw_set_bit (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw_stop_master(struct ipw_priv *priv)
{
	int rc;

	IPW_DEBUG_TRACE(">>\n");
	/* stop master. typical delay - 0 */
	ipw_set_bit(priv, IPW_RESET_REG, IPW_RESET_REG_STOP_MASTER);

	/* timeout is in msec, polled in 10-msec quanta */
	rc = ipw_poll_bit(priv, IPW_RESET_REG,
			  IPW_RESET_REG_MASTER_DISABLED, 100);
	if (rc < 0) {
		IPW_ERROR("wait for stop master failed after 100ms\n");
		return -1;
	}

	IPW_DEBUG_INFO("stop master %dms\n", rc);

	return rc;
}