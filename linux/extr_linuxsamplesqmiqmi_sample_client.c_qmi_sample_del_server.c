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
struct qmi_service {struct platform_device* priv; } ;
struct qmi_handle {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

__attribute__((used)) static void qmi_sample_del_server(struct qmi_handle *qmi,
				  struct qmi_service *service)
{
	struct platform_device *pdev = service->priv;

	platform_device_unregister(pdev);
}