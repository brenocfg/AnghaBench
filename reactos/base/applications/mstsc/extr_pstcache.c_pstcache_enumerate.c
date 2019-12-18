#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int uint16 ;
typedef  int sint16 ;
struct TYPE_3__ {scalar_t__ stamp; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  HASH_KEY ;
typedef  TYPE_1__ CELLHEADER ;

/* Variables and functions */
 int BMPCACHE2_NUM_PSTCELLS ; 
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 scalar_t__ IS_PERSISTENT (size_t) ; 
 int MAX_CELL_SIZE ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  cache_rebuild_bmpcache_linked_list (size_t,int*,int) ; 
 scalar_t__ g_bitmap_cache ; 
 scalar_t__ g_bitmap_cache_persist_enable ; 
 scalar_t__ g_bitmap_cache_precache ; 
 int g_pstcache_Bpp ; 
 scalar_t__ g_pstcache_enumerated ; 
 int* g_pstcache_fd ; 
 int g_server_depth ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pstcache_load_bitmap (size_t,int) ; 
 int /*<<< orphan*/  rd_lseek_file (int,int) ; 
 scalar_t__ rd_read_file (int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  zero_key ; 

int
pstcache_enumerate(uint8 id, HASH_KEY * keylist)
{
	int fd, n;
	uint16 idx;
	sint16 mru_idx[0xa00];
	uint32 mru_stamp[0xa00];
	CELLHEADER cellhdr;

	if (!(g_bitmap_cache && g_bitmap_cache_persist_enable && IS_PERSISTENT(id)))
		return 0;

	/* The server disconnects if the bitmap cache content is sent more than once */
	if (g_pstcache_enumerated)
		return 0;

	DEBUG_RDP5(("Persistent bitmap cache enumeration... "));
	for (idx = 0; idx < BMPCACHE2_NUM_PSTCELLS; idx++)
	{
		fd = g_pstcache_fd[id];
		rd_lseek_file(fd, idx * (g_pstcache_Bpp * MAX_CELL_SIZE + sizeof(CELLHEADER)));
		if (rd_read_file(fd, &cellhdr, sizeof(CELLHEADER)) <= 0)
			break;

		if (memcmp(cellhdr.key, zero_key, sizeof(HASH_KEY)) != 0)
		{
			memcpy(keylist[idx], cellhdr.key, sizeof(HASH_KEY));

			/* Pre-cache (not possible for 8 bit colour depth cause it needs a colourmap) */
			if (g_bitmap_cache_precache && cellhdr.stamp && g_server_depth > 8)
				pstcache_load_bitmap(id, idx);

			/* Sort by stamp */
			for (n = idx; n > 0 && cellhdr.stamp < mru_stamp[n - 1]; n--)
			{
				mru_idx[n] = mru_idx[n - 1];
				mru_stamp[n] = mru_stamp[n - 1];
			}

			mru_idx[n] = idx;
			mru_stamp[n] = cellhdr.stamp;
		}
		else
		{
			break;
		}
	}

	DEBUG_RDP5(("%d cached bitmaps.\n", idx));

	cache_rebuild_bmpcache_linked_list(id, mru_idx, idx);
	g_pstcache_enumerated = True;
	return idx;
}