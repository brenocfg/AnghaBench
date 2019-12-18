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
struct _HPDF_CCITT_Data {TYPE_1__* tif_rawdata; TYPE_1__* tif_data; } ;
struct TYPE_3__ {struct TYPE_3__* runs; struct TYPE_3__* refline; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__ HPDF_Fax3CodecState ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static HPDF_STATUS HPDF_FreeCCITTFax3(struct _HPDF_CCITT_Data *pData)
{
	if(pData->tif_data!=NULL) {
		HPDF_Fax3CodecState* esp=pData->tif_data;
		if(esp->refline!=NULL) {
			free(esp->refline);
			esp->refline=NULL;
		}
		if(esp->runs!=NULL) {
			free(esp->runs);
			esp->runs=NULL;
		}
		free(pData->tif_data);
		pData->tif_data=NULL;
	}
	if(pData->tif_rawdata!=NULL) {
		free(pData->tif_rawdata);
		pData->tif_rawdata=NULL;
	}
	return HPDF_OK;
}