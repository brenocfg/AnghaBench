#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_7__ {int tif_flags; int /*<<< orphan*/  tif_name; int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  field_name; int /*<<< orphan*/  field_oktochange; } ;
typedef  TYPE_1__ TIFFField ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* TIFFFindField (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TIFFTAG_IMAGELENGTH ; 
 int /*<<< orphan*/  TIFF_ANY ; 
 int TIFF_BEENWRITING ; 
 scalar_t__ isPseudoTag (scalar_t__) ; 

__attribute__((used)) static int
OkToChangeTag(TIFF* tif, uint32 tag)
{
	const TIFFField* fip = TIFFFindField(tif, tag, TIFF_ANY);
	if (!fip) {			/* unknown tag */
		TIFFErrorExt(tif->tif_clientdata, "TIFFSetField", "%s: Unknown %stag %u",
		    tif->tif_name, isPseudoTag(tag) ? "pseudo-" : "", tag);
		return (0);
	}
	if (tag != TIFFTAG_IMAGELENGTH && (tif->tif_flags & TIFF_BEENWRITING) &&
	    !fip->field_oktochange) {
		/*
		 * Consult info table to see if tag can be changed
		 * after we've started writing.  We only allow changes
		 * to those tags that don't/shouldn't affect the
		 * compression and/or format of the data.
		 */
		TIFFErrorExt(tif->tif_clientdata, "TIFFSetField",
		    "%s: Cannot modify tag \"%s\" while writing",
		    tif->tif_name, fip->field_name);
		return (0);
	}
	return (1);
}