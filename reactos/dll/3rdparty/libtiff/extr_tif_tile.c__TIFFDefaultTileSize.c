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
typedef  int uint32 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int TIFFroundup_32 (int,int) ; 

void
_TIFFDefaultTileSize(TIFF* tif, uint32* tw, uint32* th)
{
	(void) tif;
	if (*(int32*) tw < 1)
		*tw = 256;
	if (*(int32*) th < 1)
		*th = 256;
	/* roundup to a multiple of 16 per the spec */
	if (*tw & 0xf)
		*tw = TIFFroundup_32(*tw, 16);
	if (*th & 0xf)
		*th = TIFFroundup_32(*th, 16);
}