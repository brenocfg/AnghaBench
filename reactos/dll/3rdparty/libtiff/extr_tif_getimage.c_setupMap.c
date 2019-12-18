#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_6__ {int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_5__ {long bitspersample; void** Map; scalar_t__ photometric; TYPE_4__* tif; } ;
typedef  void* TIFFRGBValue ;
typedef  TYPE_1__ TIFFRGBAImage ;

/* Variables and functions */
 scalar_t__ PHOTOMETRIC_MINISBLACK ; 
 scalar_t__ PHOTOMETRIC_MINISWHITE ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TIFFFileName (TYPE_4__*) ; 
 int /*<<< orphan*/  _TIFFfree (void**) ; 
 scalar_t__ _TIFFmalloc (int) ; 
 int /*<<< orphan*/  makebwmap (TYPE_1__*) ; 

__attribute__((used)) static int
setupMap(TIFFRGBAImage* img)
{
    int32 x, range;

    range = (int32)((1L<<img->bitspersample)-1);
    
    /* treat 16 bit the same as eight bit */
    if( img->bitspersample == 16 )
        range = (int32) 255;

    img->Map = (TIFFRGBValue*) _TIFFmalloc((range+1) * sizeof (TIFFRGBValue));
    if (img->Map == NULL) {
		TIFFErrorExt(img->tif->tif_clientdata, TIFFFileName(img->tif),
			"No space for photometric conversion table");
		return (0);
    }
    if (img->photometric == PHOTOMETRIC_MINISWHITE) {
	for (x = 0; x <= range; x++)
	    img->Map[x] = (TIFFRGBValue) (((range - x) * 255) / range);
    } else {
	for (x = 0; x <= range; x++)
	    img->Map[x] = (TIFFRGBValue) ((x * 255) / range);
    }
    if (img->bitspersample <= 16 &&
	(img->photometric == PHOTOMETRIC_MINISBLACK ||
	 img->photometric == PHOTOMETRIC_MINISWHITE)) {
	/*
	 * Use photometric mapping table to construct
	 * unpacking tables for samples <= 8 bits.
	 */
	if (!makebwmap(img))
	    return (0);
	/* no longer need Map, free it */
	_TIFFfree(img->Map);
	img->Map = NULL;
    }
    return (1);
}