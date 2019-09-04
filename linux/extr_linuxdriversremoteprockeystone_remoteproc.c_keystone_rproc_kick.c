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
struct rproc {struct keystone_rproc* priv; } ;
struct keystone_rproc {scalar_t__ kick_gpio; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  gpio_set_value (scalar_t__,int) ; 

__attribute__((used)) static void keystone_rproc_kick(struct rproc *rproc, int vqid)
{
	struct keystone_rproc *ksproc = rproc->priv;

	if (WARN_ON(ksproc->kick_gpio < 0))
		return;

	gpio_set_value(ksproc->kick_gpio, 1);
}