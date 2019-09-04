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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  tmsize_t ;
struct TYPE_3__ {int (* encoderow ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* encodepfunc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ TIFFPredictorState ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 TYPE_1__* PredictorState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
PredictorEncodeRow(TIFF* tif, uint8* bp, tmsize_t cc, uint16 s)
{
	TIFFPredictorState *sp = PredictorState(tif);

	assert(sp != NULL);
	assert(sp->encodepfunc != NULL);
	assert(sp->encoderow != NULL);

	/* XXX horizontal differencing alters user's data XXX */
	if( !(*sp->encodepfunc)(tif, bp, cc) )
        return 0;
	return (*sp->encoderow)(tif, bp, cc, s);
}