#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_8__ {int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_6__ {int /*<<< orphan*/ * any; } ;
struct TYPE_7__ {int (* get ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_5__* tif; TYPE_1__ put; } ;
typedef  TYPE_2__ TIFFRGBAImage ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TIFFFileName (TYPE_5__*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
TIFFRGBAImageGet(TIFFRGBAImage* img, uint32* raster, uint32 w, uint32 h)
{
    if (img->get == NULL) {
		TIFFErrorExt(img->tif->tif_clientdata, TIFFFileName(img->tif), "No \"get\" routine setup");
		return (0);
	}
	if (img->put.any == NULL) {
		TIFFErrorExt(img->tif->tif_clientdata, TIFFFileName(img->tif),
		"No \"put\" routine setupl; probably can not handle image format");
		return (0);
    }
    return (*img->get)(img, raster, w, h);
}