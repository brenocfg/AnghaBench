#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _HPDF_CCITT_Data {TYPE_1__* tif_data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * faxdcs; int /*<<< orphan*/ * subaddress; scalar_t__ recvparams; scalar_t__ groupoptions; } ;
struct TYPE_5__ {int /*<<< orphan*/ * runs; int /*<<< orphan*/ * refline; } ;
typedef  int HPDF_STATUS ;
typedef  TYPE_1__ HPDF_Fax3CodecState ;
typedef  TYPE_2__ HPDF_Fax3BaseState ;

/* Variables and functions */
 TYPE_1__* EncoderState (struct _HPDF_CCITT_Data*) ; 
 TYPE_2__* Fax3State (struct _HPDF_CCITT_Data*) ; 
 int HPDF_OK ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static HPDF_STATUS HPDF_InitCCITTFax3(struct _HPDF_CCITT_Data *pData)
{
	HPDF_Fax3BaseState* sp;
	HPDF_Fax3CodecState* esp;

	/*
	 * Allocate state block so tag methods have storage to record values.
	 */
	pData->tif_data = (HPDF_Fax3CodecState *)
		malloc(sizeof (HPDF_Fax3CodecState));

	if (pData->tif_data == NULL) {
		return 1;
	}

	sp = Fax3State(pData);
    /* sp->rw_mode = pData->tif_mode; */

	/*
	 * Override parent get/set field methods.
	 */
	sp->groupoptions = 0;	
	sp->recvparams = 0;
	sp->subaddress = NULL;
	sp->faxdcs = NULL;

	esp = EncoderState(pData);
	esp->refline = NULL;
	esp->runs = NULL;

	return HPDF_OK;
}