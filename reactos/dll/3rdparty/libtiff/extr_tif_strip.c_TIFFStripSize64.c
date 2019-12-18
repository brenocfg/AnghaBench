#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  scalar_t__ uint32 ;
struct TYPE_5__ {scalar_t__ td_rowsperstrip; scalar_t__ td_imagelength; } ;
struct TYPE_6__ {TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFVStripSize64 (TYPE_2__*,scalar_t__) ; 

uint64
TIFFStripSize64(TIFF* tif)
{
	TIFFDirectory* td = &tif->tif_dir;
	uint32 rps = td->td_rowsperstrip;
	if (rps > td->td_imagelength)
		rps = td->td_imagelength;
	return (TIFFVStripSize64(tif, rps));
}