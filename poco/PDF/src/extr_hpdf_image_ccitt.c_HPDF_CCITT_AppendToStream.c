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
typedef  int /*<<< orphan*/  tsize_t ;
typedef  int /*<<< orphan*/  tidata_t ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  int HPDF_STATUS ;

/* Variables and functions */
 scalar_t__ HPDF_OK ; 
 scalar_t__ HPDF_Stream_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HPDF_STATUS 
HPDF_CCITT_AppendToStream(HPDF_Stream  dst, 	
						  tidata_t	tif_rawdata,
						  tsize_t	tif_rawcc)
{
	if(HPDF_Stream_Write(dst, tif_rawdata, tif_rawcc)!=HPDF_OK)
		return 1;
	return HPDF_OK;
}