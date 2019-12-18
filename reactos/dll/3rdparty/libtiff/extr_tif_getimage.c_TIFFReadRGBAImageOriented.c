#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  scalar_t__ uint16 ;
struct TYPE_11__ {int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_10__ {int height; scalar_t__ req_orientation; } ;
typedef  TYPE_1__ TIFFRGBAImage ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  TIFFFileName (TYPE_2__*) ; 
 scalar_t__ TIFFRGBAImageBegin (TYPE_1__*,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  TIFFRGBAImageEnd (TYPE_1__*) ; 
 int TIFFRGBAImageGet (TYPE_1__*,int*,int,int) ; 
 scalar_t__ TIFFRGBAImageOK (TYPE_2__*,char*) ; 

int
TIFFReadRGBAImageOriented(TIFF* tif,
			  uint32 rwidth, uint32 rheight, uint32* raster,
			  int orientation, int stop)
{
    char emsg[1024] = "";
    TIFFRGBAImage img;
    int ok;

	if (TIFFRGBAImageOK(tif, emsg) && TIFFRGBAImageBegin(&img, tif, stop, emsg)) {
		img.req_orientation = (uint16)orientation;
		/* XXX verify rwidth and rheight against width and height */
		ok = TIFFRGBAImageGet(&img, raster+(rheight-img.height)*rwidth,
			rwidth, img.height);
		TIFFRGBAImageEnd(&img);
	} else {
		TIFFErrorExt(tif->tif_clientdata, TIFFFileName(tif), "%s", emsg);
		ok = 0;
    }
    return (ok);
}