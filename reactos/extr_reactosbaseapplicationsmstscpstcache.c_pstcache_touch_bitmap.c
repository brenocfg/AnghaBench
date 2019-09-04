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
typedef  size_t uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  stamp ;
typedef  int /*<<< orphan*/  CELLHEADER ;

/* Variables and functions */
 int BMPCACHE2_NUM_PSTCELLS ; 
 int /*<<< orphan*/  IS_PERSISTENT (size_t) ; 
 int MAX_CELL_SIZE ; 
 int g_pstcache_Bpp ; 
 int* g_pstcache_fd ; 
 int /*<<< orphan*/  rd_lseek_file (int,int) ; 
 int /*<<< orphan*/  rd_write_file (int,int /*<<< orphan*/ *,int) ; 

void
pstcache_touch_bitmap(uint8 cache_id, uint16 cache_idx, uint32 stamp)
{
	int fd;

	if (!IS_PERSISTENT(cache_id) || cache_idx >= BMPCACHE2_NUM_PSTCELLS)
		return;

	fd = g_pstcache_fd[cache_id];
	rd_lseek_file(fd, 12 + cache_idx * (g_pstcache_Bpp * MAX_CELL_SIZE + sizeof(CELLHEADER)));
	rd_write_file(fd, &stamp, sizeof(stamp));
}