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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int tmsize_t ;
struct TYPE_9__ {int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_8__ {int rowsize; int /*<<< orphan*/  (* decodepfunc ) (TYPE_2__*,int /*<<< orphan*/ *,int) ;scalar_t__ (* decodetile ) (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ TIFFPredictorState ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 TYPE_1__* PredictorState (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
PredictorDecodeTile(TIFF* tif, uint8* op0, tmsize_t occ0, uint16 s)
{
	TIFFPredictorState *sp = PredictorState(tif);

	assert(sp != NULL);
	assert(sp->decodetile != NULL);

	if ((*sp->decodetile)(tif, op0, occ0, s)) {
		tmsize_t rowsize = sp->rowsize;
		assert(rowsize > 0);
		if((occ0%rowsize) !=0)
        {
            TIFFErrorExt(tif->tif_clientdata, "PredictorDecodeTile",
                         "%s", "occ0%rowsize != 0");
            return 0;
        }
		assert(sp->decodepfunc != NULL);
		while (occ0 > 0) {
			if( !(*sp->decodepfunc)(tif, op0, rowsize) )
                return 0;
			occ0 -= rowsize;
			op0 += rowsize;
		}
		return 1;
	} else
		return 0;
}