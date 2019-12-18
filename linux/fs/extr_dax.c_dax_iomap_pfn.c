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
struct iomap {int /*<<< orphan*/  dax_dev; int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t PFN_PHYS (long) ; 
 int PHYS_PFN (size_t) ; 
 int bdev_dax_pgoff (int /*<<< orphan*/ ,int /*<<< orphan*/  const,size_t,int /*<<< orphan*/ *) ; 
 long dax_direct_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dax_iomap_sector (struct iomap*,int /*<<< orphan*/ ) ; 
 int dax_read_lock () ; 
 int /*<<< orphan*/  dax_read_unlock (int) ; 
 int /*<<< orphan*/  pfn_t_devmap (int /*<<< orphan*/ ) ; 
 int pfn_t_to_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dax_iomap_pfn(struct iomap *iomap, loff_t pos, size_t size,
			 pfn_t *pfnp)
{
	const sector_t sector = dax_iomap_sector(iomap, pos);
	pgoff_t pgoff;
	int id, rc;
	long length;

	rc = bdev_dax_pgoff(iomap->bdev, sector, size, &pgoff);
	if (rc)
		return rc;
	id = dax_read_lock();
	length = dax_direct_access(iomap->dax_dev, pgoff, PHYS_PFN(size),
				   NULL, pfnp);
	if (length < 0) {
		rc = length;
		goto out;
	}
	rc = -EINVAL;
	if (PFN_PHYS(length) < size)
		goto out;
	if (pfn_t_to_pfn(*pfnp) & (PHYS_PFN(size)-1))
		goto out;
	/* For larger pages we need devmap */
	if (length > 1 && !pfn_t_devmap(*pfnp))
		goto out;
	rc = 0;
out:
	dax_read_unlock(id);
	return rc;
}