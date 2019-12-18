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
struct TYPE_3__ {int predictor; int /*<<< orphan*/  (* printdir ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ;} ;
typedef  TYPE_1__ TIFFPredictorState ;
typedef  int /*<<< orphan*/  TIFF ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREDICTOR ; 
 TYPE_1__* PredictorState (int /*<<< orphan*/ *) ; 
 scalar_t__ TIFFFieldSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static void
PredictorPrintDir(TIFF* tif, FILE* fd, long flags)
{
	TIFFPredictorState* sp = PredictorState(tif);

	(void) flags;
	if (TIFFFieldSet(tif,FIELD_PREDICTOR)) {
		fprintf(fd, "  Predictor: ");
		switch (sp->predictor) {
			case 1: fprintf(fd, "none "); break;
			case 2: fprintf(fd, "horizontal differencing "); break;
			case 3: fprintf(fd, "floating point predictor "); break;
		}
		fprintf(fd, "%d (0x%x)\n", sp->predictor, sp->predictor);
	}
	if (sp->printdir)
		(*sp->printdir)(tif, fd, flags);
}