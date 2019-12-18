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
struct q6core {struct q6core* svc_version; scalar_t__ get_version_supported; struct q6core* fwk_version; scalar_t__ fwk_version_supported; } ;
struct apr_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct q6core* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_core ; 
 int /*<<< orphan*/  kfree (struct q6core*) ; 

__attribute__((used)) static int q6core_exit(struct apr_device *adev)
{
	struct q6core *core = dev_get_drvdata(&adev->dev);

	if (core->fwk_version_supported)
		kfree(core->fwk_version);
	if (core->get_version_supported)
		kfree(core->svc_version);

	g_core = NULL;
	kfree(core);

	return 0;
}