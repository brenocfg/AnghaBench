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
struct platform_device {int dummy; } ;
struct iproc_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iproc_pcie_shutdown (struct iproc_pcie*) ; 
 struct iproc_pcie* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void iproc_pcie_pltfm_shutdown(struct platform_device *pdev)
{
	struct iproc_pcie *pcie = platform_get_drvdata(pdev);

	iproc_pcie_shutdown(pcie);
}