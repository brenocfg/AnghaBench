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
 int /*<<< orphan*/  CBD_RESET_REG_PRINCETON_RESET ; 
 int /*<<< orphan*/  IPW_DEBUG_TRACE (char*) ; 
 int /*<<< orphan*/  IPW_RESET_REG ; 
 int /*<<< orphan*/  ipw_clear_bit (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void ipw_arc_release(struct ipw_priv *priv)
{
	IPW_DEBUG_TRACE(">>\n");
	mdelay(5);

	ipw_clear_bit(priv, IPW_RESET_REG, CBD_RESET_REG_PRINCETON_RESET);

	/* no one knows timing, for safety add some delay */
	mdelay(5);
}