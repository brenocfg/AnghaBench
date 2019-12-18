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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  ORIENTATION_BOTLEFT ; 
 int TIFFReadRGBAImageOriented (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
TIFFReadRGBAImage(TIFF* tif,
		  uint32 rwidth, uint32 rheight, uint32* raster, int stop)
{
	return TIFFReadRGBAImageOriented(tif, rwidth, rheight, raster,
					 ORIENTATION_BOTLEFT, stop);
}