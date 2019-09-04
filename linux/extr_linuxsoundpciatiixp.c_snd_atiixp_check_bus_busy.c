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
struct atiixp {int dummy; } ;

/* Variables and functions */
 int ATI_REG_CMD_RECEIVE_EN ; 
 int ATI_REG_CMD_SEND_EN ; 
 int ATI_REG_CMD_SPDF_OUT_EN ; 
 unsigned int ATI_REG_IER_SET_BUS_BUSY ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  IER ; 
 int atiixp_read (struct atiixp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_update (struct atiixp*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void snd_atiixp_check_bus_busy(struct atiixp *chip)
{
	unsigned int bus_busy;
	if (atiixp_read(chip, CMD) & (ATI_REG_CMD_SEND_EN |
				      ATI_REG_CMD_RECEIVE_EN |
				      ATI_REG_CMD_SPDF_OUT_EN))
		bus_busy = ATI_REG_IER_SET_BUS_BUSY;
	else
		bus_busy = 0;
	atiixp_update(chip, IER, ATI_REG_IER_SET_BUS_BUSY, bus_busy);
}