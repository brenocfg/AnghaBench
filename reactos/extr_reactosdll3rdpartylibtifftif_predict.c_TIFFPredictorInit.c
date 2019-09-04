#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  printdir; int /*<<< orphan*/  vsetfield; int /*<<< orphan*/  vgetfield; } ;
struct TYPE_10__ {int /*<<< orphan*/  tif_setupencode; int /*<<< orphan*/  tif_setupdecode; TYPE_1__ tif_tagmethods; int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_9__ {int predictor; int /*<<< orphan*/ * decodepfunc; int /*<<< orphan*/ * encodepfunc; int /*<<< orphan*/  setupencode; int /*<<< orphan*/  setupdecode; int /*<<< orphan*/  printdir; int /*<<< orphan*/  vsetparent; int /*<<< orphan*/  vgetparent; } ;
typedef  TYPE_2__ TIFFPredictorState ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  PredictorPrintDir ; 
 int /*<<< orphan*/  PredictorSetupDecode ; 
 int /*<<< orphan*/  PredictorSetupEncode ; 
 TYPE_2__* PredictorState (TYPE_3__*) ; 
 int /*<<< orphan*/  PredictorVGetField ; 
 int /*<<< orphan*/  PredictorVSetField ; 
 int /*<<< orphan*/  TIFFArrayCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  _TIFFMergeFields (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  predictFields ; 

int
TIFFPredictorInit(TIFF* tif)
{
	TIFFPredictorState* sp = PredictorState(tif);

	assert(sp != 0);

	/*
	 * Merge codec-specific tag information.
	 */
	if (!_TIFFMergeFields(tif, predictFields,
			      TIFFArrayCount(predictFields))) {
		TIFFErrorExt(tif->tif_clientdata, "TIFFPredictorInit",
		    "Merging Predictor codec-specific tags failed");
		return 0;
	}

	/*
	 * Override parent get/set field methods.
	 */
	sp->vgetparent = tif->tif_tagmethods.vgetfield;
	tif->tif_tagmethods.vgetfield =
            PredictorVGetField;/* hook for predictor tag */
	sp->vsetparent = tif->tif_tagmethods.vsetfield;
	tif->tif_tagmethods.vsetfield =
	    PredictorVSetField;/* hook for predictor tag */
	sp->printdir = tif->tif_tagmethods.printdir;
	tif->tif_tagmethods.printdir =
            PredictorPrintDir;	/* hook for predictor tag */

	sp->setupdecode = tif->tif_setupdecode;
	tif->tif_setupdecode = PredictorSetupDecode;
	sp->setupencode = tif->tif_setupencode;
	tif->tif_setupencode = PredictorSetupEncode;

	sp->predictor = 1;			/* default value */
	sp->encodepfunc = NULL;			/* no predictor routine */
	sp->decodepfunc = NULL;			/* no predictor routine */
	return 1;
}