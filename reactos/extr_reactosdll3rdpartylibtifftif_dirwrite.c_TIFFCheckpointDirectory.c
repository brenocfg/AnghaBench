#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * td_stripoffset; } ;
struct TYPE_9__ {TYPE_1__ tif_dir; } ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  TIFFSeekFile (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFSetWriteOffset (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFSetupStrips (TYPE_2__*) ; 
 int TIFFWriteDirectorySec (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

int
TIFFCheckpointDirectory(TIFF* tif)
{
	int rc;
	/* Setup the strips arrays, if they haven't already been. */
	if (tif->tif_dir.td_stripoffset == NULL)
	    (void) TIFFSetupStrips(tif);
	rc = TIFFWriteDirectorySec(tif,TRUE,FALSE,NULL);
	(void) TIFFSetWriteOffset(tif, TIFFSeekFile(tif, 0, SEEK_END));
	return rc;
}