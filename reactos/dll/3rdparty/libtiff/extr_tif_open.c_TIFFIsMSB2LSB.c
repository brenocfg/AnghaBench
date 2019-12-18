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
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  FILLORDER_MSB2LSB ; 
 int isFillOrder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
TIFFIsMSB2LSB(TIFF* tif)
{
	return (isFillOrder(tif, FILLORDER_MSB2LSB));
}