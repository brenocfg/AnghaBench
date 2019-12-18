#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_6__ {int winsect; int csize; int /*<<< orphan*/  pdrv; int /*<<< orphan*/ * win; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_OK ; 
 int MAX_MALLOC ; 
 scalar_t__ RES_OK ; 
 int SS (TYPE_1__*) ; 
 int clst2sect (TYPE_1__*,int) ; 
 scalar_t__ disk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * ff_memalloc (int) ; 
 int /*<<< orphan*/  ff_memfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sync_window (TYPE_1__*) ; 

__attribute__((used)) static FRESULT dir_clear (	/* Returns FR_OK or FR_DISK_ERR */
	FATFS *fs,		/* Filesystem object */
	DWORD clst		/* Directory table to clear */
)
{
	DWORD sect;
	UINT n, szb;
	BYTE *ibuf;


	if (sync_window(fs) != FR_OK) return FR_DISK_ERR;	/* Flush disk access window */
	sect = clst2sect(fs, clst);		/* Top of the cluster */
	fs->winsect = sect;				/* Set window to top of the cluster */
	mem_set(fs->win, 0, sizeof fs->win);	/* Clear window buffer */
#if FF_USE_LFN == 3		/* Quick table clear by using multi-secter write */
	/* Allocate a temporary buffer */
	for (szb = ((DWORD)fs->csize * SS(fs) >= MAX_MALLOC) ? MAX_MALLOC : fs->csize * SS(fs), ibuf = 0; szb > SS(fs) && (ibuf = ff_memalloc(szb)) == 0; szb /= 2) ;
	if (szb > SS(fs)) {		/* Buffer allocated? */
		mem_set(ibuf, 0, szb);
		szb /= SS(fs);		/* Bytes -> Sectors */
		for (n = 0; n < fs->csize && disk_write(fs->pdrv, ibuf, sect + n, szb) == RES_OK; n += szb) ;	/* Fill the cluster with 0 */
		ff_memfree(ibuf);
	} else
#endif
	{
		ibuf = fs->win; szb = 1;	/* Use window buffer (many single-sector writes may take a time) */
		for (n = 0; n < fs->csize && disk_write(fs->pdrv, ibuf, sect + n, szb) == RES_OK; n += szb) ;	/* Fill the cluster with 0 */
	}
	return (n == fs->csize) ? FR_OK : FR_DISK_ERR;
}