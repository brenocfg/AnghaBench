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
struct gntdev_priv {int dummy; } ;
struct gntdev_grant_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct gntdev_grant_map* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GNTDEV_DMA_FLAG_COHERENT ; 
 int GNTDEV_DMA_FLAG_WC ; 
 int gntdev_account_mapped_pages (int) ; 
 struct gntdev_grant_map* gntdev_alloc_map (struct gntdev_priv*,int,int) ; 
 int /*<<< orphan*/  gntdev_put_map (int /*<<< orphan*/ *,struct gntdev_grant_map*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct gntdev_grant_map *
dmabuf_exp_alloc_backing_storage(struct gntdev_priv *priv, int dmabuf_flags,
				 int count)
{
	struct gntdev_grant_map *map;

	if (unlikely(count <= 0))
		return ERR_PTR(-EINVAL);

	if ((dmabuf_flags & GNTDEV_DMA_FLAG_WC) &&
	    (dmabuf_flags & GNTDEV_DMA_FLAG_COHERENT)) {
		pr_debug("Wrong dma-buf flags: 0x%x\n", dmabuf_flags);
		return ERR_PTR(-EINVAL);
	}

	map = gntdev_alloc_map(priv, count, dmabuf_flags);
	if (!map)
		return ERR_PTR(-ENOMEM);

	if (unlikely(gntdev_account_mapped_pages(count))) {
		pr_debug("can't map %d pages: over limit\n", count);
		gntdev_put_map(NULL, map);
		return ERR_PTR(-ENOMEM);
	}
	return map;
}