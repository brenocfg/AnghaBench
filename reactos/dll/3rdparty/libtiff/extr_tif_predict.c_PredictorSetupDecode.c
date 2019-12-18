#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int td_bitspersample; } ;
struct TYPE_11__ {scalar_t__ tif_decoderow; int tif_flags; void* tif_postdecode; void* tif_decodetile; void* tif_decodestrip; TYPE_2__ tif_dir; } ;
struct TYPE_9__ {int predictor; scalar_t__ decodepfunc; scalar_t__ decoderow; void* decodetile; void* decodestrip; int /*<<< orphan*/  (* setupdecode ) (TYPE_3__*) ;} ;
typedef  TYPE_1__ TIFFPredictorState ;
typedef  TYPE_2__ TIFFDirectory ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 scalar_t__ PredictorDecodeRow ; 
 void* PredictorDecodeTile ; 
 int /*<<< orphan*/  PredictorSetup (TYPE_3__*) ; 
 TYPE_1__* PredictorState (TYPE_3__*) ; 
 int TIFF_SWAB ; 
 void* _TIFFNoPostDecode ; 
 scalar_t__ fpAcc ; 
 scalar_t__ horAcc16 ; 
 scalar_t__ horAcc32 ; 
 scalar_t__ horAcc8 ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 scalar_t__ swabHorAcc16 ; 
 scalar_t__ swabHorAcc32 ; 

__attribute__((used)) static int
PredictorSetupDecode(TIFF* tif)
{
	TIFFPredictorState* sp = PredictorState(tif);
	TIFFDirectory* td = &tif->tif_dir;

	/* Note: when PredictorSetup() fails, the effets of setupdecode() */
	/* will not be "cancelled" so setupdecode() might be robust to */
	/* be called several times. */
	if (!(*sp->setupdecode)(tif) || !PredictorSetup(tif))
		return 0;

	if (sp->predictor == 2) {
		switch (td->td_bitspersample) {
			case 8:  sp->decodepfunc = horAcc8; break;
			case 16: sp->decodepfunc = horAcc16; break;
			case 32: sp->decodepfunc = horAcc32; break;
		}
		/*
		 * Override default decoding method with one that does the
		 * predictor stuff.
		 */
                if( tif->tif_decoderow != PredictorDecodeRow )
                {
                    sp->decoderow = tif->tif_decoderow;
                    tif->tif_decoderow = PredictorDecodeRow;
                    sp->decodestrip = tif->tif_decodestrip;
                    tif->tif_decodestrip = PredictorDecodeTile;
                    sp->decodetile = tif->tif_decodetile;
                    tif->tif_decodetile = PredictorDecodeTile;
                }

		/*
		 * If the data is horizontally differenced 16-bit data that
		 * requires byte-swapping, then it must be byte swapped before
		 * the accumulation step.  We do this with a special-purpose
		 * routine and override the normal post decoding logic that
		 * the library setup when the directory was read.
		 */
		if (tif->tif_flags & TIFF_SWAB) {
			if (sp->decodepfunc == horAcc16) {
				sp->decodepfunc = swabHorAcc16;
				tif->tif_postdecode = _TIFFNoPostDecode;
            } else if (sp->decodepfunc == horAcc32) {
				sp->decodepfunc = swabHorAcc32;
				tif->tif_postdecode = _TIFFNoPostDecode;
            }
		}
	}

	else if (sp->predictor == 3) {
		sp->decodepfunc = fpAcc;
		/*
		 * Override default decoding method with one that does the
		 * predictor stuff.
		 */
                if( tif->tif_decoderow != PredictorDecodeRow )
                {
                    sp->decoderow = tif->tif_decoderow;
                    tif->tif_decoderow = PredictorDecodeRow;
                    sp->decodestrip = tif->tif_decodestrip;
                    tif->tif_decodestrip = PredictorDecodeTile;
                    sp->decodetile = tif->tif_decodetile;
                    tif->tif_decodetile = PredictorDecodeTile;
                }
		/*
		 * The data should not be swapped outside of the floating
		 * point predictor, the accumulation routine should return
		 * byres in the native order.
		 */
		if (tif->tif_flags & TIFF_SWAB) {
			tif->tif_postdecode = _TIFFNoPostDecode;
		}
		/*
		 * Allocate buffer to keep the decoded bytes before
		 * rearranging in the right order
		 */
	}

	return 1;
}