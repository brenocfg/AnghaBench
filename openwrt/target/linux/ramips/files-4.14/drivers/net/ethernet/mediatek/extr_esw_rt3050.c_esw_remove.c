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
struct rt305x_esw {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT305X_ESW_REG_IMR ; 
 int /*<<< orphan*/  esw_w32 (struct rt305x_esw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rt305x_esw* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esw_remove(struct platform_device *pdev)
{
	struct rt305x_esw *esw = platform_get_drvdata(pdev);

	if (esw) {
		esw_w32(esw, ~0, RT305X_ESW_REG_IMR);
		platform_set_drvdata(pdev, NULL);
	}

	return 0;
}