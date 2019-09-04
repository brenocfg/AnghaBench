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
typedef  void* uint32 ;
struct TYPE_5__ {void* tif_curstrip; void* tif_row; scalar_t__ tif_curoff; scalar_t__ tif_nextdiroff; scalar_t__ tif_diroff; } ;
typedef  int /*<<< orphan*/  TIFFFieldArray ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFDefaultDirectory (TYPE_1__*) ; 
 int /*<<< orphan*/  _TIFFSetupFields (TYPE_1__*,int /*<<< orphan*/  const*) ; 

int
TIFFCreateCustomDirectory(TIFF* tif, const TIFFFieldArray* infoarray)
{
	TIFFDefaultDirectory(tif);

	/*
	 * Reset the field definitions to match the application provided list. 
	 * Hopefully TIFFDefaultDirectory() won't have done anything irreversable
	 * based on it's assumption this is an image directory.
	 */
	_TIFFSetupFields(tif, infoarray);

	tif->tif_diroff = 0;
	tif->tif_nextdiroff = 0;
	tif->tif_curoff = 0;
	tif->tif_row = (uint32) -1;
	tif->tif_curstrip = (uint32) -1;

	return 0;
}