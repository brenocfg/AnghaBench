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
struct _HPDF_CCITT_Data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rowbytes; } ;
struct TYPE_5__ {int bit; scalar_t__ line; scalar_t__ maxk; scalar_t__ k; TYPE_1__ b; scalar_t__ refline; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__ HPDF_Fax3CodecState ;

/* Variables and functions */
 TYPE_2__* EncoderState (struct _HPDF_CCITT_Data*) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HPDF_STATUS 
HPDF_Fax3PreEncode(struct _HPDF_CCITT_Data *pData/*, tsample_t s*/)
{
	HPDF_Fax3CodecState* sp = EncoderState(pData);

	/* assert(sp != NULL); */
	sp->bit = 8;
	sp->data = 0;
	/* sp->tag = G3_1D; */
	/*
	 * This is necessary for Group 4; otherwise it isn't
	 * needed because the first scanline of each strip ends
	 * up being copied into the refline.
	 */
	if (sp->refline)
		memset(sp->refline, 0x00, sp->b.rowbytes);
	sp->k = sp->maxk = 0;
	sp->line = 0;
	return HPDF_OK;
}