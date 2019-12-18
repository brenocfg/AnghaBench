#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_7__ {int max_block_id; TYPE_1__* blocks; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_6__ {scalar_t__ bimg_len; } ;

/* Variables and functions */
 scalar_t__ XLogRecGetTotalLen (TYPE_2__*) ; 
 scalar_t__ XLogRecHasBlockImage (TYPE_2__*,int) ; 

__attribute__((used)) static void
XLogDumpRecordLen(XLogReaderState *record, uint32 *rec_len, uint32 *fpi_len)
{
	int			block_id;

	/*
	 * Calculate the amount of FPI data in the record.
	 *
	 * XXX: We peek into xlogreader's private decoded backup blocks for the
	 * bimg_len indicating the length of FPI data. It doesn't seem worth it to
	 * add an accessor macro for this.
	 */
	*fpi_len = 0;
	for (block_id = 0; block_id <= record->max_block_id; block_id++)
	{
		if (XLogRecHasBlockImage(record, block_id))
			*fpi_len += record->blocks[block_id].bimg_len;
	}

	/*
	 * Calculate the length of the record as the total length - the length of
	 * all the block images.
	 */
	*rec_len = XLogRecGetTotalLen(record) - *fpi_len;
}