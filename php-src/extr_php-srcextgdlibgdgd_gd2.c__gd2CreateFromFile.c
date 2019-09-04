#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_chunk_info ;
typedef  TYPE_1__* gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtxPtr ;
struct TYPE_7__ {int /*<<< orphan*/  colorsTotal; } ;

/* Variables and functions */
 int /*<<< orphan*/  GD2_DBG (int /*<<< orphan*/ ) ; 
 int _gd2GetHeader (int /*<<< orphan*/ ,int*,int*,int*,int*,int*,int*,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _gdGetColors (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ gd2_truecolor (int) ; 
 int /*<<< orphan*/  gdFree (int /*<<< orphan*/ *) ; 
 TYPE_1__* gdImageCreate (int,int) ; 
 TYPE_1__* gdImageCreateTrueColor (int,int) ; 
 int /*<<< orphan*/  gdImageDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  gd_error (char*,...) ; 

__attribute__((used)) static gdImagePtr _gd2CreateFromFile (gdIOCtxPtr in, int *sx, int *sy, int *cs, int *vers, int *fmt, int *ncx, int *ncy, t_chunk_info ** cidx)
{
	gdImagePtr im;

	if (_gd2GetHeader (in, sx, sy, cs, vers, fmt, ncx, ncy, cidx) != 1) {
		GD2_DBG(gd_error("Bad GD2 header"));
		goto fail1;
	}

	if (gd2_truecolor(*fmt)) {
		im = gdImageCreateTrueColor(*sx, *sy);
	} else {
		im = gdImageCreate(*sx, *sy);
	}
	if (im == NULL) {
		GD2_DBG(gd_error("Could not create gdImage"));
		goto fail2;
	}

	if (!_gdGetColors(in, im, (*vers) == 2)) {
		GD2_DBG(gd_error("Could not read color palette"));
		goto fail3;
	}
	GD2_DBG(gd_error("Image palette completed: %d colours", im->colorsTotal));

	return im;

fail3:
	gdImageDestroy(im);
fail2:
	gdFree(*cidx);
fail1:
	return 0;
}