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
typedef  int uint64 ;
typedef  int toff_t ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int TIFFSeekFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int _TIFFSeekOK(TIFF* tif, toff_t off)
{
    /* Huge offsets, especially -1 / UINT64_MAX, can cause issues */
    /* See http://bugzilla.maptools.org/show_bug.cgi?id=2726 */
    return off <= (~(uint64)0)/2 && TIFFSeekFile(tif,off,SEEK_SET)==off;
}