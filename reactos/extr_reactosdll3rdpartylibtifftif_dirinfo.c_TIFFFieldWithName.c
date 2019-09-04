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
struct TYPE_4__ {int /*<<< orphan*/  tif_clientdata; } ;
typedef  int /*<<< orphan*/  TIFFField ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  TIFF_ANY ; 
 int /*<<< orphan*/ * _TIFFFindFieldByName (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

const TIFFField*
TIFFFieldWithName(TIFF* tif, const char *field_name)
{
	const TIFFField* fip =
		_TIFFFindFieldByName(tif, field_name, TIFF_ANY);
	if (!fip) {
		TIFFErrorExt(tif->tif_clientdata, "TIFFFieldWithName",
			     "Internal error, unknown tag %s", field_name);
	}
	return (fip);
}