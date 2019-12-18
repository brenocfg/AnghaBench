#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tsize_t ;
typedef  int /*<<< orphan*/  tidata_t ;
struct _HPDF_CCITT_Data {int dummy; } ;
struct TYPE_4__ {scalar_t__ rowbytes; int /*<<< orphan*/  rowpixels; } ;
struct TYPE_5__ {TYPE_1__ b; int /*<<< orphan*/  refline; } ;
typedef  int HPDF_STATUS ;
typedef  TYPE_2__ HPDF_Fax3CodecState ;

/* Variables and functions */
 TYPE_2__* EncoderState (struct _HPDF_CCITT_Data*) ; 
 scalar_t__ HPDF_Fax3Encode2DRow (struct _HPDF_CCITT_Data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static HPDF_STATUS 
HPDF_Fax4Encode(struct _HPDF_CCITT_Data *pData, tidata_t bp, tsize_t cc/*, tsample_t s*/)
{
	HPDF_Fax3CodecState *sp = EncoderState(pData);

	/* (void) s; */
	while ((long)cc > 0) {
		if (HPDF_Fax3Encode2DRow(pData, bp, sp->refline, sp->b.rowpixels)!=HPDF_OK)
			return 1;
		memcpy(sp->refline, bp, sp->b.rowbytes);
		bp += sp->b.rowbytes;
		cc -= sp->b.rowbytes;
	}
	return HPDF_OK;
}