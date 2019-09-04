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
struct pn533_i2c_phy {int aborted; int /*<<< orphan*/  priv; } ;
struct pn533 {struct pn533_i2c_phy* phy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  pn533_i2c_send_ack (struct pn533*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pn533_recv_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pn533_i2c_abort_cmd(struct pn533 *dev, gfp_t flags)
{
	struct pn533_i2c_phy *phy = dev->phy;

	phy->aborted = true;

	/* An ack will cancel the last issued command */
	pn533_i2c_send_ack(dev, flags);

	/* schedule cmd_complete_work to finish current command execution */
	pn533_recv_frame(phy->priv, NULL, -ENOENT);
}