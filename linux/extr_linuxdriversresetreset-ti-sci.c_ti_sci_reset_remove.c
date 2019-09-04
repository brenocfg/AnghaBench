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
struct ti_sci_reset_data {int /*<<< orphan*/  idr; int /*<<< orphan*/  rcdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 struct ti_sci_reset_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_controller_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ti_sci_reset_remove(struct platform_device *pdev)
{
	struct ti_sci_reset_data *data = platform_get_drvdata(pdev);

	reset_controller_unregister(&data->rcdev);

	idr_destroy(&data->idr);

	return 0;
}