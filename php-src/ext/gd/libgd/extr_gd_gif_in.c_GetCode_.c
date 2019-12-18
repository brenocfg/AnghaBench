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
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_3__ {int curbit; int lastbit; int last_byte; int* buf; scalar_t__ done; } ;
typedef  TYPE_1__ CODE_STATIC_DATA ;

/* Variables and functions */
 int CSD_BUF_SIZE ; 
 scalar_t__ FALSE ; 
 int GetDataBlock (int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static int
GetCode_(gdIOCtx *fd, CODE_STATIC_DATA *scd, int code_size, int flag, int *ZeroDataBlockP)
{
	int           i, j, ret;
	int           count;

	if (flag) {
		scd->curbit = 0;
		scd->lastbit = 0;
		scd->last_byte = 2;
		scd->done = FALSE;
		return 0;
	}

	if ( (scd->curbit + code_size) >= scd->lastbit) {
		if (scd->done) {
			if (scd->curbit >= scd->lastbit) {
				/* Oh well */
			}
			return -1;
		}
		scd->buf[0] = scd->buf[scd->last_byte-2];
		scd->buf[1] = scd->buf[scd->last_byte-1];

               if ((count = GetDataBlock(fd, &scd->buf[2], ZeroDataBlockP)) <= 0)
			scd->done = TRUE;

		scd->last_byte = 2 + count;
		scd->curbit = (scd->curbit - scd->lastbit) + 16;
		scd->lastbit = (2+count)*8 ;
	}

	if ((scd->curbit + code_size - 1) >= (CSD_BUF_SIZE * 8)) {
		ret = -1;
	} else {
		ret = 0;
		for (i = scd->curbit, j = 0; j < code_size; ++i, ++j) {
			ret |= ((scd->buf[i / 8] & (1 << (i % 8))) != 0) << j;
		}
	}

	scd->curbit += code_size;
	return ret;
}