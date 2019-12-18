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
struct ext4_map_blocks {int m_len; scalar_t__ m_lblk; int m_flags; } ;
struct mpage_da_data {int /*<<< orphan*/  do_map; struct ext4_map_blocks map; } ;
struct buffer_head {int b_state; } ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int BH_FLAGS ; 
 int MAX_WRITEPAGES_EXTENT_LEN ; 
 int /*<<< orphan*/  buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_unwritten (struct buffer_head*) ; 

__attribute__((used)) static bool mpage_add_bh_to_extent(struct mpage_da_data *mpd, ext4_lblk_t lblk,
				   struct buffer_head *bh)
{
	struct ext4_map_blocks *map = &mpd->map;

	/* Buffer that doesn't need mapping for writeback? */
	if (!buffer_dirty(bh) || !buffer_mapped(bh) ||
	    (!buffer_delay(bh) && !buffer_unwritten(bh))) {
		/* So far no extent to map => we write the buffer right away */
		if (map->m_len == 0)
			return true;
		return false;
	}

	/* First block in the extent? */
	if (map->m_len == 0) {
		/* We cannot map unless handle is started... */
		if (!mpd->do_map)
			return false;
		map->m_lblk = lblk;
		map->m_len = 1;
		map->m_flags = bh->b_state & BH_FLAGS;
		return true;
	}

	/* Don't go larger than mballoc is willing to allocate */
	if (map->m_len >= MAX_WRITEPAGES_EXTENT_LEN)
		return false;

	/* Can we merge the block to our big extent? */
	if (lblk == map->m_lblk + map->m_len &&
	    (bh->b_state & BH_FLAGS) == map->m_flags) {
		map->m_len++;
		return true;
	}
	return false;
}