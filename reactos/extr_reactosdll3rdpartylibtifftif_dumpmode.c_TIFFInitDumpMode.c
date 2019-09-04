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
struct TYPE_3__ {int /*<<< orphan*/  tif_seek; void* tif_encodetile; void* tif_encodestrip; void* tif_encoderow; void* tif_decodetile; void* tif_decodestrip; void* tif_decoderow; int /*<<< orphan*/  tif_fixuptags; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  DumpFixupTags ; 
 void* DumpModeDecode ; 
 void* DumpModeEncode ; 
 int /*<<< orphan*/  DumpModeSeek ; 

int
TIFFInitDumpMode(TIFF* tif, int scheme)
{
	(void) scheme;
	tif->tif_fixuptags = DumpFixupTags;  
	tif->tif_decoderow = DumpModeDecode;
	tif->tif_decodestrip = DumpModeDecode;
	tif->tif_decodetile = DumpModeDecode;
	tif->tif_encoderow = DumpModeEncode;
	tif->tif_encodestrip = DumpModeEncode;
	tif->tif_encodetile = DumpModeEncode; 
	tif->tif_seek = DumpModeSeek;
	return (1);
}