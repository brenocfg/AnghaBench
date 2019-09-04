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
typedef  int /*<<< orphan*/  Pager ;

/* Variables and functions */

__attribute__((used)) static void pagerFixMaplimit(Pager *pPager){
#if SQLITE_MAX_MMAP_SIZE>0
  sqlite3_file *fd = pPager->fd;
  if( isOpen(fd) ){
    sqlite3_int64 sz;
    pPager->bUseFetch = (fd->pMethods->iVersion>=3) && pPager->szMmap>0;
    sz = pPager->szMmap;
    sqlite3OsFileControlHint(pPager->fd, SQLITE_FCNTL_MMAP_SIZE, &sz);
  }
#endif
}