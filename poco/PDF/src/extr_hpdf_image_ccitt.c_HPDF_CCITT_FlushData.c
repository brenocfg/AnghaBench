#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct _HPDF_CCITT_Data {scalar_t__ tif_rawcc; int /*<<< orphan*/  tif_rawdata; int /*<<< orphan*/  tif_rawcp; int /*<<< orphan*/  dst; } ;
typedef  int HPDF_STATUS ;

/* Variables and functions */
 scalar_t__ HPDF_CCITT_AppendToStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HPDF_OK ; 

__attribute__((used)) static HPDF_STATUS 
HPDF_CCITT_FlushData(struct _HPDF_CCITT_Data *pData)
{
	if (pData->tif_rawcc > 0) {
		/*if (!isFillOrder(tif, tif->tif_dir.td_fillorder) &&
		    (tif->tif_flags & TIFF_NOBITREV) == 0)
			TIFFReverseBits((unsigned char *pData->tif_rawdata,
			    pData->tif_rawcc);*/
		if (HPDF_CCITT_AppendToStream(pData->dst,
		    pData->tif_rawdata, pData->tif_rawcc)!=HPDF_OK)
			return 1;
		pData->tif_rawcc = 0;
		pData->tif_rawcp = pData->tif_rawdata;
	}
	return HPDF_OK;
}