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
typedef  int tmsize_t ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFSwabArrayOfShort (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  horDiff16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
swabHorDiff16(TIFF* tif, uint8* cp0, tmsize_t cc)
{
    uint16* wp = (uint16*) cp0;
    tmsize_t wc = cc / 2;

    if( !horDiff16(tif, cp0, cc) )
        return 0;

    TIFFSwabArrayOfShort(wp, wc);
    return 1;
}