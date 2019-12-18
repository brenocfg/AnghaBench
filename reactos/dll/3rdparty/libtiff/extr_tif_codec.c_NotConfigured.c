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
struct TYPE_3__ {void* tif_setupencode; void* tif_encodestatus; void* tif_setupdecode; void* tif_decodestatus; void* tif_fixuptags; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 void* FALSE ; 
 void* _notConfigured ; 

__attribute__((used)) static int
NotConfigured(TIFF* tif, int scheme)
{
	(void) scheme;

	tif->tif_fixuptags = _notConfigured;
	tif->tif_decodestatus = FALSE;
	tif->tif_setupdecode = _notConfigured;
	tif->tif_encodestatus = FALSE;
	tif->tif_setupencode = _notConfigured;
	return (1);
}