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
typedef  scalar_t__ u32 ;
struct netlbl_lsm_catmap {scalar_t__ startbit; scalar_t__* bitmap; struct netlbl_lsm_catmap* next; } ;
typedef  int NETLBL_CATMAP_MAPTYPE ;

/* Variables and functions */
 int ENOENT ; 
 int NETLBL_CATMAP_BIT ; 
 scalar_t__ NETLBL_CATMAP_MAPCNT ; 
 scalar_t__ NETLBL_CATMAP_MAPSIZE ; 
 int /*<<< orphan*/  _CM_F_WALK ; 
 struct netlbl_lsm_catmap* _netlbl_catmap_getnode (struct netlbl_lsm_catmap**,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int netlbl_catmap_walk(struct netlbl_lsm_catmap *catmap, u32 offset)
{
	struct netlbl_lsm_catmap *iter;
	u32 idx;
	u32 bit;
	NETLBL_CATMAP_MAPTYPE bitmap;

	iter = _netlbl_catmap_getnode(&catmap, offset, _CM_F_WALK, 0);
	if (iter == NULL)
		return -ENOENT;
	if (offset > iter->startbit) {
		offset -= iter->startbit;
		idx = offset / NETLBL_CATMAP_MAPSIZE;
		bit = offset % NETLBL_CATMAP_MAPSIZE;
	} else {
		idx = 0;
		bit = 0;
	}
	bitmap = iter->bitmap[idx] >> bit;

	for (;;) {
		if (bitmap != 0) {
			while ((bitmap & NETLBL_CATMAP_BIT) == 0) {
				bitmap >>= 1;
				bit++;
			}
			return iter->startbit +
			       (NETLBL_CATMAP_MAPSIZE * idx) + bit;
		}
		if (++idx >= NETLBL_CATMAP_MAPCNT) {
			if (iter->next != NULL) {
				iter = iter->next;
				idx = 0;
			} else
				return -ENOENT;
		}
		bitmap = iter->bitmap[idx];
		bit = 0;
	}

	return -ENOENT;
}