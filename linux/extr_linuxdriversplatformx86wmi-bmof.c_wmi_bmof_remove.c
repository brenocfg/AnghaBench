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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct wmi_device {TYPE_1__ dev; } ;
struct bmof_priv {int /*<<< orphan*/  bmofdata; int /*<<< orphan*/  bmof_bin_attr; } ;

/* Variables and functions */
 struct bmof_priv* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wmi_bmof_remove(struct wmi_device *wdev)
{
	struct bmof_priv *priv = dev_get_drvdata(&wdev->dev);

	sysfs_remove_bin_file(&wdev->dev.kobj, &priv->bmof_bin_attr);
	kfree(priv->bmofdata);
	return 0;
}