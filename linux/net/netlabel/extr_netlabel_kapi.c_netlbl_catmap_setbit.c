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
typedef  size_t u32 ;
struct netlbl_lsm_catmap {size_t* bitmap; scalar_t__ startbit; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NETLBL_CATMAP_BIT ; 
 size_t NETLBL_CATMAP_MAPSIZE ; 
 int /*<<< orphan*/  _CM_F_ALLOC ; 
 struct netlbl_lsm_catmap* _netlbl_catmap_getnode (struct netlbl_lsm_catmap**,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int netlbl_catmap_setbit(struct netlbl_lsm_catmap **catmap,
			 u32 bit,
			 gfp_t flags)
{
	struct netlbl_lsm_catmap *iter;
	u32 idx;

	iter = _netlbl_catmap_getnode(catmap, bit, _CM_F_ALLOC, flags);
	if (iter == NULL)
		return -ENOMEM;

	bit -= iter->startbit;
	idx = bit / NETLBL_CATMAP_MAPSIZE;
	iter->bitmap[idx] |= NETLBL_CATMAP_BIT << (bit % NETLBL_CATMAP_MAPSIZE);

	return 0;
}