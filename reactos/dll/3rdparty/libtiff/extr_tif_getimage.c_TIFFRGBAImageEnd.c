#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * bluecmap; int /*<<< orphan*/ * greencmap; int /*<<< orphan*/ * redcmap; int /*<<< orphan*/ * Bitdepth16To8; int /*<<< orphan*/ * UaToAa; int /*<<< orphan*/ * cielab; int /*<<< orphan*/ * ycbcr; int /*<<< orphan*/ * PALmap; int /*<<< orphan*/ * BWmap; int /*<<< orphan*/ * Map; } ;
typedef  TYPE_1__ TIFFRGBAImage ;

/* Variables and functions */
 int /*<<< orphan*/  _TIFFfree (int /*<<< orphan*/ *) ; 

void
TIFFRGBAImageEnd(TIFFRGBAImage* img)
{
	if (img->Map) {
		_TIFFfree(img->Map);
		img->Map = NULL;
	}
	if (img->BWmap) {
		_TIFFfree(img->BWmap);
		img->BWmap = NULL;
	}
	if (img->PALmap) {
		_TIFFfree(img->PALmap);
		img->PALmap = NULL;
	}
	if (img->ycbcr) {
		_TIFFfree(img->ycbcr);
		img->ycbcr = NULL;
	}
	if (img->cielab) {
		_TIFFfree(img->cielab);
		img->cielab = NULL;
	}
	if (img->UaToAa) {
		_TIFFfree(img->UaToAa);
		img->UaToAa = NULL;
	}
	if (img->Bitdepth16To8) {
		_TIFFfree(img->Bitdepth16To8);
		img->Bitdepth16To8 = NULL;
	}

	if( img->redcmap ) {
		_TIFFfree( img->redcmap );
		_TIFFfree( img->greencmap );
		_TIFFfree( img->bluecmap );
                img->redcmap = img->greencmap = img->bluecmap = NULL;
	}
}