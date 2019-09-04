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
struct TYPE_2__ {int /*<<< orphan*/ * queue_priority; } ;
struct mwifiex_private {TYPE_1__ wmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMM_AC_BE ; 
 int /*<<< orphan*/  WMM_AC_BK ; 
 int /*<<< orphan*/  WMM_AC_VI ; 
 int /*<<< orphan*/  WMM_AC_VO ; 

__attribute__((used)) static void mwifiex_wmm_default_queue_priorities(struct mwifiex_private *priv)
{
	/* Default queue priorities: VO->VI->BE->BK */
	priv->wmm.queue_priority[0] = WMM_AC_VO;
	priv->wmm.queue_priority[1] = WMM_AC_VI;
	priv->wmm.queue_priority[2] = WMM_AC_BE;
	priv->wmm.queue_priority[3] = WMM_AC_BK;
}