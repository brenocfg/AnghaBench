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
typedef  int u32 ;
struct tsi721_device {scalar_t__ regs; } ;
struct rio_mport {struct tsi721_device* priv; } ;

/* Variables and functions */
 scalar_t__ TSI721_RIO_EM_INT_ENABLE ; 
 int TSI721_RIO_EM_INT_ENABLE_PW_RX ; 
 scalar_t__ TSI721_RIO_PW_RX_STAT ; 
 int TSI721_RIO_PW_RX_STAT_PW_DISC ; 
 int TSI721_RIO_PW_RX_STAT_PW_VAL ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static int tsi721_pw_enable(struct rio_mport *mport, int enable)
{
	struct tsi721_device *priv = mport->priv;
	u32 rval;

	rval = ioread32(priv->regs + TSI721_RIO_EM_INT_ENABLE);

	if (enable)
		rval |= TSI721_RIO_EM_INT_ENABLE_PW_RX;
	else
		rval &= ~TSI721_RIO_EM_INT_ENABLE_PW_RX;

	/* Clear pending PW interrupts */
	iowrite32(TSI721_RIO_PW_RX_STAT_PW_DISC | TSI721_RIO_PW_RX_STAT_PW_VAL,
		  priv->regs + TSI721_RIO_PW_RX_STAT);
	/* Update enable bits */
	iowrite32(rval, priv->regs + TSI721_RIO_EM_INT_ENABLE);

	return 0;
}