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
typedef  int /*<<< orphan*/  toff_t ;
typedef  int /*<<< orphan*/  TIFFFieldArray ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int TIFFReadCustomDirectory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * _TIFFGetExifFields () ; 

int
TIFFReadEXIFDirectory(TIFF* tif, toff_t diroff)
{
	const TIFFFieldArray* exifFieldArray;
	exifFieldArray = _TIFFGetExifFields();
	return TIFFReadCustomDirectory(tif, diroff, exifFieldArray);  
}