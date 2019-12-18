#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_9__ {int /*<<< orphan*/  tif_flags; } ;
struct TYPE_8__ {int (* vsetparent ) (TYPE_2__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  predictor; } ;
typedef  TYPE_1__ TIFFPredictorState ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREDICTOR ; 
 TYPE_1__* PredictorState (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFFSetFieldBit (TYPE_2__*,int /*<<< orphan*/ ) ; 
#define  TIFFTAG_PREDICTOR 128 
 int /*<<< orphan*/  TIFF_DIRTYDIRECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint16_vap ; 
 int /*<<< orphan*/  va_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
PredictorVSetField(TIFF* tif, uint32 tag, va_list ap)
{
	TIFFPredictorState *sp = PredictorState(tif);

	assert(sp != NULL);
	assert(sp->vsetparent != NULL);

	switch (tag) {
	case TIFFTAG_PREDICTOR:
		sp->predictor = (uint16) va_arg(ap, uint16_vap);
		TIFFSetFieldBit(tif, FIELD_PREDICTOR);
		break;
	default:
		return (*sp->vsetparent)(tif, tag, ap);
	}
	tif->tif_flags |= TIFF_DIRTYDIRECT;
	return 1;
}