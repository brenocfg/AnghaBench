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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  tmsize_t ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int TIFFNoEncode (int /*<<< orphan*/ *,char*) ; 

int
_TIFFNoTileEncode(TIFF* tif, uint8* pp, tmsize_t cc, uint16 s)
{
	(void) pp; (void) cc; (void) s;
	return (TIFFNoEncode(tif, "tile"));
}