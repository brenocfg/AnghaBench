#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  xlog_seg_size; } ;
typedef  TYPE_1__ ControlFileData ;

/* Variables and functions */
 int /*<<< orphan*/  IsValidWalSegSize (int /*<<< orphan*/ ) ; 
 size_t PG_CONTROL_FILE_SIZE ; 
 int /*<<< orphan*/  WalSegSz ; 
 int /*<<< orphan*/  checkControlFile (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  ngettext (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*,int,...) ; 

__attribute__((used)) static void
digestControlFile(ControlFileData *ControlFile, char *src, size_t size)
{
	if (size != PG_CONTROL_FILE_SIZE)
		pg_fatal("unexpected control file size %d, expected %d",
				 (int) size, PG_CONTROL_FILE_SIZE);

	memcpy(ControlFile, src, sizeof(ControlFileData));

	/* set and validate WalSegSz */
	WalSegSz = ControlFile->xlog_seg_size;

	if (!IsValidWalSegSize(WalSegSz))
		pg_fatal(ngettext("WAL segment size must be a power of two between 1 MB and 1 GB, but the control file specifies %d byte",
						  "WAL segment size must be a power of two between 1 MB and 1 GB, but the control file specifies %d bytes",
						  WalSegSz),
				 WalSegSz);

	/* Additional checks on control file */
	checkControlFile(ControlFile);
}