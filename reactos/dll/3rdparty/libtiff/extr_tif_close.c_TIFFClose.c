#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thandle_t ;
struct TYPE_4__ {int /*<<< orphan*/  tif_clientdata; int /*<<< orphan*/  (* tif_closeproc ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  (* TIFFCloseProc ) (int /*<<< orphan*/ ) ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFCleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
TIFFClose(TIFF* tif)
{
	TIFFCloseProc closeproc = tif->tif_closeproc;
	thandle_t fd = tif->tif_clientdata;

	TIFFCleanup(tif);
	(void) (*closeproc)(fd);
}