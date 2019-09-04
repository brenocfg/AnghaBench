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
typedef  int /*<<< orphan*/  u32 ;
struct ntb_dev {int dummy; } ;
struct intel_ntb_dev {TYPE_1__* self_reg; scalar_t__ self_mmio; } ;
struct TYPE_2__ {scalar_t__ spad; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndev_spad_read (struct intel_ntb_dev*,int,scalar_t__) ; 
 struct intel_ntb_dev* ntb_ndev (struct ntb_dev*) ; 

u32 intel_ntb_spad_read(struct ntb_dev *ntb, int idx)
{
	struct intel_ntb_dev *ndev = ntb_ndev(ntb);

	return ndev_spad_read(ndev, idx,
			      ndev->self_mmio +
			      ndev->self_reg->spad);
}