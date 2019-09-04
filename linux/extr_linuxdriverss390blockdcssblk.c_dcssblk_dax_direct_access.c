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
struct dcssblk_dev_info {int dummy; } ;
struct dax_device {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 long __dcssblk_direct_access (struct dcssblk_dev_info*,int /*<<< orphan*/ ,long,void**,int /*<<< orphan*/ *) ; 
 struct dcssblk_dev_info* dax_get_private (struct dax_device*) ; 

__attribute__((used)) static long
dcssblk_dax_direct_access(struct dax_device *dax_dev, pgoff_t pgoff,
		long nr_pages, void **kaddr, pfn_t *pfn)
{
	struct dcssblk_dev_info *dev_info = dax_get_private(dax_dev);

	return __dcssblk_direct_access(dev_info, pgoff, nr_pages, kaddr, pfn);
}