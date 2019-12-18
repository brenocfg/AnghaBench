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
typedef  int uint64 ;
struct TYPE_3__ {int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,char const*) ; 

uint64
_TIFFMultiply64(TIFF* tif, uint64 first, uint64 second, const char* where)
{
	uint64 bytes = first * second;

	if (second && bytes / second != first) {
		TIFFErrorExt(tif->tif_clientdata, where, "Integer overflow in %s", where);
		bytes = 0;
	}

	return bytes;
}