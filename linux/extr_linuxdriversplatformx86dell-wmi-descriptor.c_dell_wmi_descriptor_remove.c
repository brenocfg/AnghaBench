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
struct wmi_device {int /*<<< orphan*/  dev; } ;
struct descriptor_priv {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct descriptor_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dell_wmi_descriptor_remove(struct wmi_device *wdev)
{
	struct descriptor_priv *priv = dev_get_drvdata(&wdev->dev);

	mutex_lock(&list_mutex);
	list_del(&priv->list);
	mutex_unlock(&list_mutex);
	return 0;
}