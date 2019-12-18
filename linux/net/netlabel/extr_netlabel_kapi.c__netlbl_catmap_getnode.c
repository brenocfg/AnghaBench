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
struct netlbl_lsm_catmap {scalar_t__ startbit; struct netlbl_lsm_catmap* next; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ NETLBL_CATMAP_SIZE ; 
 unsigned int _CM_F_ALLOC ; 
 unsigned int _CM_F_WALK ; 
 struct netlbl_lsm_catmap* netlbl_catmap_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netlbl_lsm_catmap *_netlbl_catmap_getnode(
					     struct netlbl_lsm_catmap **catmap,
					     u32 offset,
					     unsigned int cm_flags,
					     gfp_t gfp_flags)
{
	struct netlbl_lsm_catmap *iter = *catmap;
	struct netlbl_lsm_catmap *prev = NULL;

	if (iter == NULL)
		goto catmap_getnode_alloc;
	if (offset < iter->startbit)
		goto catmap_getnode_walk;
	while (iter && offset >= (iter->startbit + NETLBL_CATMAP_SIZE)) {
		prev = iter;
		iter = iter->next;
	}
	if (iter == NULL || offset < iter->startbit)
		goto catmap_getnode_walk;

	return iter;

catmap_getnode_walk:
	if (cm_flags & _CM_F_WALK)
		return iter;
catmap_getnode_alloc:
	if (!(cm_flags & _CM_F_ALLOC))
		return NULL;

	iter = netlbl_catmap_alloc(gfp_flags);
	if (iter == NULL)
		return NULL;
	iter->startbit = offset & ~(NETLBL_CATMAP_SIZE - 1);

	if (prev == NULL) {
		iter->next = *catmap;
		*catmap = iter;
	} else {
		iter->next = prev->next;
		prev->next = iter;
	}

	return iter;
}