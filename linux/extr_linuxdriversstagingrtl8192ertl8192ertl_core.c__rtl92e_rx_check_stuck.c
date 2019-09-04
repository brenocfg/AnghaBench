#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct r8192_priv {TYPE_1__* ops; } ;
struct net_device {int dummy; } ;
typedef  enum reset_type { ____Placeholder_reset_type } reset_type ;
struct TYPE_2__ {scalar_t__ (* RxCheckStuckHandler ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RESET ; 
 int RESET_TYPE_NORESET ; 
 int RESET_TYPE_SILENT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*) ; 

__attribute__((used)) static enum reset_type _rtl92e_rx_check_stuck(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	if (priv->ops->RxCheckStuckHandler(dev)) {
		RT_TRACE(COMP_RESET, "RxStuck Condition\n");
		return RESET_TYPE_SILENT;
	}

	return RESET_TYPE_NORESET;
}