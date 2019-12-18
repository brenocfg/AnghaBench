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
struct ocfs2_super {int dummy; } ;
struct ocfs2_reservation_map {int /*<<< orphan*/  m_lru; int /*<<< orphan*/  m_reservations; struct ocfs2_super* m_osb; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  memset (struct ocfs2_reservation_map*,int /*<<< orphan*/ ,int) ; 

int ocfs2_resmap_init(struct ocfs2_super *osb,
		      struct ocfs2_reservation_map *resmap)
{
	memset(resmap, 0, sizeof(*resmap));

	resmap->m_osb = osb;
	resmap->m_reservations = RB_ROOT;
	/* m_bitmap_len is initialized to zero by the above memset. */
	INIT_LIST_HEAD(&resmap->m_lru);

	return 0;
}