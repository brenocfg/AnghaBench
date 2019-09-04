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
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct Scsi_Host* aha1542_hw_init (int /*<<< orphan*/ *,struct device*,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  driver_template ; 

__attribute__((used)) static int aha1542_isa_match(struct device *pdev, unsigned int ndev)
{
	struct Scsi_Host *sh = aha1542_hw_init(&driver_template, pdev, ndev);

	if (!sh)
		return 0;

	dev_set_drvdata(pdev, sh);
	return 1;
}