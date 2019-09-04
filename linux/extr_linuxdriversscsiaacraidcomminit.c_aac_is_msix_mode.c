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
struct aac_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  OMR; } ;

/* Variables and functions */
 int AAC_INT_MODE_MSIX ; 
 TYPE_1__ MUnit ; 
 scalar_t__ aac_is_src (struct aac_dev*) ; 
 int src_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int aac_is_msix_mode(struct aac_dev *dev)
{
	u32 status = 0;

	if (aac_is_src(dev))
		status = src_readl(dev, MUnit.OMR);
	return (status & AAC_INT_MODE_MSIX);
}