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
struct ism_dev {scalar_t__ ieq_dma_addr; int /*<<< orphan*/ * ieq; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ISM_ERROR ; 
 int /*<<< orphan*/  ISM_UNREG_IEQ ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int ism_cmd_simple (struct ism_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unregister_ieq(struct ism_dev *ism)
{
	int ret;

	if (!ism->ieq)
		return 0;

	ret = ism_cmd_simple(ism, ISM_UNREG_IEQ);
	if (ret && ret != ISM_ERROR)
		return -EIO;

	dma_free_coherent(&ism->pdev->dev, PAGE_SIZE,
			  ism->ieq, ism->ieq_dma_addr);

	ism->ieq = NULL;
	ism->ieq_dma_addr = 0;

	return 0;
}