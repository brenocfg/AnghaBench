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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  tmsize_t ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFCheckRead (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TIFFCheckTile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFComputeTile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _TIFFReadEncodedTileAndAllocBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tmsize_t
_TIFFReadTileAndAllocBuffer(TIFF* tif,
                            void **buf, tmsize_t bufsizetoalloc,
                            uint32 x, uint32 y, uint32 z, uint16 s)
{
    if (!TIFFCheckRead(tif, 1) || !TIFFCheckTile(tif, x, y, z, s))
            return ((tmsize_t)(-1));
    return (_TIFFReadEncodedTileAndAllocBuffer(tif,
                                               TIFFComputeTile(tif, x, y, z, s),
                                               buf, bufsizetoalloc,
                                               (tmsize_t)(-1)));
}