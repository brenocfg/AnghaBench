#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fastMode; scalar_t__ tableLog; } ;
struct TYPE_3__ {scalar_t__ nbBits; int /*<<< orphan*/  symbol; scalar_t__ newState; } ;
typedef  TYPE_1__ FSE_decode_t ;
typedef  TYPE_2__ FSE_DTableHeader ;
typedef  int /*<<< orphan*/  FSE_DTable ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

size_t FSE_buildDTable_rle(FSE_DTable *dt, BYTE symbolValue)
{
	void *ptr = dt;
	FSE_DTableHeader *const DTableH = (FSE_DTableHeader *)ptr;
	void *dPtr = dt + 1;
	FSE_decode_t *const cell = (FSE_decode_t *)dPtr;

	DTableH->tableLog = 0;
	DTableH->fastMode = 0;

	cell->newState = 0;
	cell->symbol = symbolValue;
	cell->nbBits = 0;

	return 0;
}