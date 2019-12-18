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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int tmsize_t ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFSwabArrayOfLong (int /*<<< orphan*/ *,int) ; 
 int horAcc32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
swabHorAcc32(TIFF* tif, uint8* cp0, tmsize_t cc)
{
	uint32* wp = (uint32*) cp0;
	tmsize_t wc = cc / 4;

        TIFFSwabArrayOfLong(wp, wc);
	return horAcc32(tif, cp0, cc);
}