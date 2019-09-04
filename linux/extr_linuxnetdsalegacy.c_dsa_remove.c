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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dsa_switch_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_of_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_remove_dst (struct dsa_switch_tree*) ; 
 struct dsa_switch_tree* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dsa_remove(struct platform_device *pdev)
{
	struct dsa_switch_tree *dst = platform_get_drvdata(pdev);

	dsa_remove_dst(dst);
	dsa_of_remove(&pdev->dev);

	return 0;
}