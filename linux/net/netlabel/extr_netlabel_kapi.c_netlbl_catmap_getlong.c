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
struct netlbl_lsm_catmap {int startbit; int* bitmap; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int EINVAL ; 
 int NETLBL_CATMAP_MAPSIZE ; 
 int /*<<< orphan*/  _CM_F_WALK ; 
 struct netlbl_lsm_catmap* _netlbl_catmap_getnode (struct netlbl_lsm_catmap**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int netlbl_catmap_getlong(struct netlbl_lsm_catmap *catmap,
			  u32 *offset,
			  unsigned long *bitmap)
{
	struct netlbl_lsm_catmap *iter;
	u32 off = *offset;
	u32 idx;

	/* only allow aligned offsets */
	if ((off & (BITS_PER_LONG - 1)) != 0)
		return -EINVAL;

	if (off < catmap->startbit) {
		off = catmap->startbit;
		*offset = off;
	}
	iter = _netlbl_catmap_getnode(&catmap, off, _CM_F_WALK, 0);
	if (iter == NULL) {
		*offset = (u32)-1;
		return 0;
	}

	if (off < iter->startbit) {
		*offset = iter->startbit;
		off = 0;
	} else
		off -= iter->startbit;
	idx = off / NETLBL_CATMAP_MAPSIZE;
	*bitmap = iter->bitmap[idx] >> (off % NETLBL_CATMAP_MAPSIZE);

	return 0;
}