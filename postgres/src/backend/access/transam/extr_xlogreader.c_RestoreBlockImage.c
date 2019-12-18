#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_6__ {int ReadRecPtr; TYPE_3__* blocks; } ;
typedef  TYPE_1__ XLogReaderState ;
struct TYPE_8__ {char* bkp_image; int bimg_info; scalar_t__ hole_length; scalar_t__ hole_offset; int /*<<< orphan*/  bimg_len; int /*<<< orphan*/  has_image; int /*<<< orphan*/  in_use; } ;
struct TYPE_7__ {char* data; } ;
typedef  TYPE_2__ PGAlignedBlock ;
typedef  TYPE_3__ DecodedBkpBlock ;

/* Variables and functions */
 int BKPIMAGE_IS_COMPRESSED ; 
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 scalar_t__ pglz_decompress (char*,int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  report_invalid_record (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

bool
RestoreBlockImage(XLogReaderState *record, uint8 block_id, char *page)
{
	DecodedBkpBlock *bkpb;
	char	   *ptr;
	PGAlignedBlock tmp;

	if (!record->blocks[block_id].in_use)
		return false;
	if (!record->blocks[block_id].has_image)
		return false;

	bkpb = &record->blocks[block_id];
	ptr = bkpb->bkp_image;

	if (bkpb->bimg_info & BKPIMAGE_IS_COMPRESSED)
	{
		/* If a backup block image is compressed, decompress it */
		if (pglz_decompress(ptr, bkpb->bimg_len, tmp.data,
							BLCKSZ - bkpb->hole_length, true) < 0)
		{
			report_invalid_record(record, "invalid compressed image at %X/%X, block %d",
								  (uint32) (record->ReadRecPtr >> 32),
								  (uint32) record->ReadRecPtr,
								  block_id);
			return false;
		}
		ptr = tmp.data;
	}

	/* generate page, taking into account hole if necessary */
	if (bkpb->hole_length == 0)
	{
		memcpy(page, ptr, BLCKSZ);
	}
	else
	{
		memcpy(page, ptr, bkpb->hole_offset);
		/* must zero-fill the hole */
		MemSet(page + bkpb->hole_offset, 0, bkpb->hole_length);
		memcpy(page + (bkpb->hole_offset + bkpb->hole_length),
			   ptr + bkpb->hole_offset,
			   BLCKSZ - (bkpb->hole_offset + bkpb->hole_length));
	}

	return true;
}