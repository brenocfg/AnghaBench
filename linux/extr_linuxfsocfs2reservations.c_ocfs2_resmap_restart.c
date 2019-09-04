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
struct ocfs2_reservation_map {unsigned int m_bitmap_len; char* m_disk_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_resmap_clear_all_resv (struct ocfs2_reservation_map*) ; 
 scalar_t__ ocfs2_resmap_disabled (struct ocfs2_reservation_map*) ; 
 int /*<<< orphan*/  resv_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ocfs2_resmap_restart(struct ocfs2_reservation_map *resmap,
			  unsigned int clen, char *disk_bitmap)
{
	if (ocfs2_resmap_disabled(resmap))
		return;

	spin_lock(&resv_lock);

	ocfs2_resmap_clear_all_resv(resmap);
	resmap->m_bitmap_len = clen;
	resmap->m_disk_bitmap = disk_bitmap;

	spin_unlock(&resv_lock);
}