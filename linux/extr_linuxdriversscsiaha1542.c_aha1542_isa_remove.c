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

/* Variables and functions */
 int /*<<< orphan*/  aha1542_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aha1542_isa_remove(struct device *pdev,
				    unsigned int ndev)
{
	aha1542_release(dev_get_drvdata(pdev));
	dev_set_drvdata(pdev, NULL);
	return 0;
}