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
struct intel_ntb_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XEON_DB_MSIX_VECTOR_COUNT ; 
 int /*<<< orphan*/  XEON_DB_MSIX_VECTOR_SHIFT ; 
 int /*<<< orphan*/  XEON_DB_TOTAL_SHIFT ; 
 int ndev_init_isr (struct intel_ntb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xeon_init_isr(struct intel_ntb_dev *ndev)
{
	return ndev_init_isr(ndev, XEON_DB_MSIX_VECTOR_COUNT,
			     XEON_DB_MSIX_VECTOR_COUNT,
			     XEON_DB_MSIX_VECTOR_SHIFT,
			     XEON_DB_TOTAL_SHIFT);
}