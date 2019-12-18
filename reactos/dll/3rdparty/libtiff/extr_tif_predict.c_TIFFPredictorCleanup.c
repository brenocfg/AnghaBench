#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  printdir; int /*<<< orphan*/  vsetfield; int /*<<< orphan*/  vgetfield; } ;
struct TYPE_9__ {int /*<<< orphan*/  tif_setupencode; int /*<<< orphan*/  tif_setupdecode; TYPE_1__ tif_tagmethods; } ;
struct TYPE_8__ {int /*<<< orphan*/  setupencode; int /*<<< orphan*/  setupdecode; int /*<<< orphan*/  printdir; int /*<<< orphan*/  vsetparent; int /*<<< orphan*/  vgetparent; } ;
typedef  TYPE_2__ TIFFPredictorState ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 TYPE_2__* PredictorState (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 

int
TIFFPredictorCleanup(TIFF* tif)
{
	TIFFPredictorState* sp = PredictorState(tif);

	assert(sp != 0);

	tif->tif_tagmethods.vgetfield = sp->vgetparent;
	tif->tif_tagmethods.vsetfield = sp->vsetparent;
	tif->tif_tagmethods.printdir = sp->printdir;
	tif->tif_setupdecode = sp->setupdecode;
	tif->tif_setupencode = sp->setupencode;

	return 1;
}