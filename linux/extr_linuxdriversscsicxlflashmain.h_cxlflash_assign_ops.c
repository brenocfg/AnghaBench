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
struct dev_dependent_vals {int dummy; } ;
struct cxlflash_backend_ops {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct cxlflash_backend_ops *
cxlflash_assign_ops(struct dev_dependent_vals *ddv)
{
	const struct cxlflash_backend_ops *ops = NULL;

#ifdef CONFIG_OCXL_BASE
	if (ddv->flags & CXLFLASH_OCXL_DEV)
		ops = &cxlflash_ocxl_ops;
#endif

#ifdef CONFIG_CXL_BASE
	if (!(ddv->flags & CXLFLASH_OCXL_DEV))
		ops = &cxlflash_cxl_ops;
#endif

	return ops;
}