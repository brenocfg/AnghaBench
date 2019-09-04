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
struct timer_list {int dummy; } ;
struct sxgbe_priv_data {int /*<<< orphan*/  eee_ctrl_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SXGBE_LPI_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eee_ctrl_timer ; 
 int /*<<< orphan*/  eee_timer ; 
 struct sxgbe_priv_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sxgbe_priv_data* priv ; 
 int /*<<< orphan*/  sxgbe_enable_eee_mode (struct sxgbe_priv_data*) ; 

__attribute__((used)) static void sxgbe_eee_ctrl_timer(struct timer_list *t)
{
	struct sxgbe_priv_data *priv = from_timer(priv, t, eee_ctrl_timer);

	sxgbe_enable_eee_mode(priv);
	mod_timer(&priv->eee_ctrl_timer, SXGBE_LPI_TIMER(eee_timer));
}