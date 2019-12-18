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
struct z_erofs_pcluster {scalar_t__ compressed_pages; int /*<<< orphan*/  clusterbits; } ;
struct z_erofs_collector {scalar_t__ compressedpages; struct z_erofs_pcluster* pcl; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct page*) ; 

__attribute__((used)) static inline bool z_erofs_try_inplace_io(struct z_erofs_collector *clt,
					  struct page *page)
{
	struct z_erofs_pcluster *const pcl = clt->pcl;
	const unsigned int clusterpages = BIT(pcl->clusterbits);

	while (clt->compressedpages < pcl->compressed_pages + clusterpages) {
		if (!cmpxchg(clt->compressedpages++, NULL, page))
			return true;
	}
	return false;
}