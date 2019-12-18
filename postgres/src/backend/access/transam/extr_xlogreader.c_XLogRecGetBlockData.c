#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
struct TYPE_4__ {TYPE_2__* blocks; } ;
typedef  TYPE_1__ XLogReaderState ;
struct TYPE_5__ {char* data; int /*<<< orphan*/  data_len; int /*<<< orphan*/  has_data; int /*<<< orphan*/  in_use; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__ DecodedBkpBlock ;

/* Variables and functions */

char *
XLogRecGetBlockData(XLogReaderState *record, uint8 block_id, Size *len)
{
	DecodedBkpBlock *bkpb;

	if (!record->blocks[block_id].in_use)
		return NULL;

	bkpb = &record->blocks[block_id];

	if (!bkpb->has_data)
	{
		if (len)
			*len = 0;
		return NULL;
	}
	else
	{
		if (len)
			*len = bkpb->data_len;
		return bkpb->data;
	}
}