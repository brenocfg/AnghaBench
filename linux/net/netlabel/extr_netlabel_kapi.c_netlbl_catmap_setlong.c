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
typedef  int u32 ;
struct netlbl_lsm_catmap {unsigned long* bitmap; scalar_t__ startbit; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int NETLBL_CATMAP_MAPSIZE ; 
 int /*<<< orphan*/  _CM_F_ALLOC ; 
 struct netlbl_lsm_catmap* _netlbl_catmap_getnode (struct netlbl_lsm_catmap**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int netlbl_catmap_setlong(struct netlbl_lsm_catmap **catmap,
			  u32 offset,
			  unsigned long bitmap,
			  gfp_t flags)
{
	struct netlbl_lsm_catmap *iter;
	u32 idx;

	/* only allow aligned offsets */
	if ((offset & (BITS_PER_LONG - 1)) != 0)
		return -EINVAL;

	iter = _netlbl_catmap_getnode(catmap, offset, _CM_F_ALLOC, flags);
	if (iter == NULL)
		return -ENOMEM;

	offset -= iter->startbit;
	idx = offset / NETLBL_CATMAP_MAPSIZE;
	iter->bitmap[idx] |= bitmap << (offset % NETLBL_CATMAP_MAPSIZE);

	return 0;
}