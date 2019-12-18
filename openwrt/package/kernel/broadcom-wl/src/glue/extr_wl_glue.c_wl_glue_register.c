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

/* Variables and functions */
 int ENOSYS ; 
#define  WL_GLUE_BUS_TYPE_BCMA 129 
#define  WL_GLUE_BUS_TYPE_SSB 128 
 int active_bus_type ; 
 int bcma_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int ssb_driver_register (int /*<<< orphan*/ *) ; 
 int wl_glue_attached ; 
 int /*<<< orphan*/  wl_glue_bcma_driver ; 
 int /*<<< orphan*/  wl_glue_ssb_driver ; 

int wl_glue_register(void)
{
	int err;

	switch(active_bus_type)
	{
#ifdef CONFIG_SSB
	case WL_GLUE_BUS_TYPE_SSB:
		err = ssb_driver_register(&wl_glue_ssb_driver);
		break;
#endif /* CONFIG_SSB */

#ifdef CONFIG_BCMA
	case WL_GLUE_BUS_TYPE_BCMA:
		err = bcma_driver_register(&wl_glue_bcma_driver);
		break;
#endif /* CONFIG_BCMA */

	default:
		pr_err("Not attaching through glue driver due to unsupported bus\n");
		err = -ENOSYS;
		break;
	}

	if (!err)
	{
		pr_info("SSB/BCMA glue driver successfully attached\n");
		wl_glue_attached = 1;
	}

	return err;
}