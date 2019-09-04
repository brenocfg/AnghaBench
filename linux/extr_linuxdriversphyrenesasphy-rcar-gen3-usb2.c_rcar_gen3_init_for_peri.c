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
struct rcar_gen3_chan {int extcon_host; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcar_gen3_enable_vbus_ctrl (struct rcar_gen3_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_gen3_set_host_mode (struct rcar_gen3_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_gen3_set_linectrl (struct rcar_gen3_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcar_gen3_init_for_peri(struct rcar_gen3_chan *ch)
{
	rcar_gen3_set_linectrl(ch, 0, 1);
	rcar_gen3_set_host_mode(ch, 0);
	rcar_gen3_enable_vbus_ctrl(ch, 0);

	ch->extcon_host = false;
	schedule_work(&ch->work);
}