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
typedef  int u32 ;
typedef  int u16 ;
struct tsi721_device {scalar_t__ odb_base; TYPE_1__* pdev; } ;
struct rio_mport {scalar_t__ sys_size; struct tsi721_device* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBELL ; 
 int RIO_TT_CODE_16 ; 
 int RIO_TT_CODE_8 ; 
 int /*<<< orphan*/  iowrite16be (int,scalar_t__) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static int tsi721_dsend(struct rio_mport *mport, int index,
			u16 destid, u16 data)
{
	struct tsi721_device *priv = mport->priv;
	u32 offset;

	offset = (((mport->sys_size) ? RIO_TT_CODE_16 : RIO_TT_CODE_8) << 18) |
		 (destid << 2);

	tsi_debug(DBELL, &priv->pdev->dev,
		  "Send Doorbell 0x%04x to destID 0x%x", data, destid);
	iowrite16be(data, priv->odb_base + offset);

	return 0;
}