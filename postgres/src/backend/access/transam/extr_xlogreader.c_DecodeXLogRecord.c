#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_8__ {scalar_t__ xl_tot_len; } ;
typedef  TYPE_1__ XLogRecord ;
struct TYPE_9__ {scalar_t__ record_origin; scalar_t__ main_data_len; scalar_t__ max_block_id; int ReadRecPtr; scalar_t__ main_data_bufsz; char* errormsg_buf; void* main_data; TYPE_3__* blocks; TYPE_1__* decoded_record; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_10__ {int in_use; int apply_image; int has_image; int has_data; scalar_t__ data_len; scalar_t__ bimg_len; scalar_t__ hole_offset; scalar_t__ bimg_info; scalar_t__ hole_length; scalar_t__ rnode; scalar_t__ blkno; char* bkp_image; scalar_t__ data_bufsz; void* data; scalar_t__ flags; scalar_t__ forknum; } ;
typedef  int /*<<< orphan*/  RepOriginId ;
typedef  scalar_t__ RelFileNode ;
typedef  TYPE_3__ DecodedBkpBlock ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BKPBLOCK_FORK_MASK ; 
 scalar_t__ BKPBLOCK_HAS_DATA ; 
 scalar_t__ BKPBLOCK_HAS_IMAGE ; 
 scalar_t__ BKPBLOCK_SAME_REL ; 
 int BKPIMAGE_APPLY ; 
 int BKPIMAGE_HAS_HOLE ; 
 int BKPIMAGE_IS_COMPRESSED ; 
 int BLCKSZ ; 
 int /*<<< orphan*/  COPY_HEADER_FIELD (scalar_t__*,int) ; 
 scalar_t__ InvalidRepOriginId ; 
 void* MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Max (scalar_t__,int) ; 
 int /*<<< orphan*/  ResetDecoder (TYPE_2__*) ; 
 scalar_t__ SizeOfXLogRecord ; 
 scalar_t__ XLR_BLOCK_ID_DATA_LONG ; 
 scalar_t__ XLR_BLOCK_ID_DATA_SHORT ; 
 scalar_t__ XLR_BLOCK_ID_ORIGIN ; 
 scalar_t__ XLR_MAX_BLOCK_ID ; 
 int /*<<< orphan*/  memcpy (void*,char*,scalar_t__) ; 
 void* palloc (scalar_t__) ; 
 int /*<<< orphan*/  pfree (void*) ; 
 int /*<<< orphan*/  report_invalid_record (TYPE_2__*,char*,scalar_t__,scalar_t__,...) ; 

bool
DecodeXLogRecord(XLogReaderState *state, XLogRecord *record, char **errormsg)
{
	/*
	 * read next _size bytes from record buffer, but check for overrun first.
	 */
#define COPY_HEADER_FIELD(_dst, _size)			\
	do {										\
		if (remaining < _size)					\
			goto shortdata_err;					\
		memcpy(_dst, ptr, _size);				\
		ptr += _size;							\
		remaining -= _size;						\
	} while(0)

	char	   *ptr;
	uint32		remaining;
	uint32		datatotal;
	RelFileNode *rnode = NULL;
	uint8		block_id;

	ResetDecoder(state);

	state->decoded_record = record;
	state->record_origin = InvalidRepOriginId;

	ptr = (char *) record;
	ptr += SizeOfXLogRecord;
	remaining = record->xl_tot_len - SizeOfXLogRecord;

	/* Decode the headers */
	datatotal = 0;
	while (remaining > datatotal)
	{
		COPY_HEADER_FIELD(&block_id, sizeof(uint8));

		if (block_id == XLR_BLOCK_ID_DATA_SHORT)
		{
			/* XLogRecordDataHeaderShort */
			uint8		main_data_len;

			COPY_HEADER_FIELD(&main_data_len, sizeof(uint8));

			state->main_data_len = main_data_len;
			datatotal += main_data_len;
			break;				/* by convention, the main data fragment is
								 * always last */
		}
		else if (block_id == XLR_BLOCK_ID_DATA_LONG)
		{
			/* XLogRecordDataHeaderLong */
			uint32		main_data_len;

			COPY_HEADER_FIELD(&main_data_len, sizeof(uint32));
			state->main_data_len = main_data_len;
			datatotal += main_data_len;
			break;				/* by convention, the main data fragment is
								 * always last */
		}
		else if (block_id == XLR_BLOCK_ID_ORIGIN)
		{
			COPY_HEADER_FIELD(&state->record_origin, sizeof(RepOriginId));
		}
		else if (block_id <= XLR_MAX_BLOCK_ID)
		{
			/* XLogRecordBlockHeader */
			DecodedBkpBlock *blk;
			uint8		fork_flags;

			if (block_id <= state->max_block_id)
			{
				report_invalid_record(state,
									  "out-of-order block_id %u at %X/%X",
									  block_id,
									  (uint32) (state->ReadRecPtr >> 32),
									  (uint32) state->ReadRecPtr);
				goto err;
			}
			state->max_block_id = block_id;

			blk = &state->blocks[block_id];
			blk->in_use = true;
			blk->apply_image = false;

			COPY_HEADER_FIELD(&fork_flags, sizeof(uint8));
			blk->forknum = fork_flags & BKPBLOCK_FORK_MASK;
			blk->flags = fork_flags;
			blk->has_image = ((fork_flags & BKPBLOCK_HAS_IMAGE) != 0);
			blk->has_data = ((fork_flags & BKPBLOCK_HAS_DATA) != 0);

			COPY_HEADER_FIELD(&blk->data_len, sizeof(uint16));
			/* cross-check that the HAS_DATA flag is set iff data_length > 0 */
			if (blk->has_data && blk->data_len == 0)
			{
				report_invalid_record(state,
									  "BKPBLOCK_HAS_DATA set, but no data included at %X/%X",
									  (uint32) (state->ReadRecPtr >> 32), (uint32) state->ReadRecPtr);
				goto err;
			}
			if (!blk->has_data && blk->data_len != 0)
			{
				report_invalid_record(state,
									  "BKPBLOCK_HAS_DATA not set, but data length is %u at %X/%X",
									  (unsigned int) blk->data_len,
									  (uint32) (state->ReadRecPtr >> 32), (uint32) state->ReadRecPtr);
				goto err;
			}
			datatotal += blk->data_len;

			if (blk->has_image)
			{
				COPY_HEADER_FIELD(&blk->bimg_len, sizeof(uint16));
				COPY_HEADER_FIELD(&blk->hole_offset, sizeof(uint16));
				COPY_HEADER_FIELD(&blk->bimg_info, sizeof(uint8));

				blk->apply_image = ((blk->bimg_info & BKPIMAGE_APPLY) != 0);

				if (blk->bimg_info & BKPIMAGE_IS_COMPRESSED)
				{
					if (blk->bimg_info & BKPIMAGE_HAS_HOLE)
						COPY_HEADER_FIELD(&blk->hole_length, sizeof(uint16));
					else
						blk->hole_length = 0;
				}
				else
					blk->hole_length = BLCKSZ - blk->bimg_len;
				datatotal += blk->bimg_len;

				/*
				 * cross-check that hole_offset > 0, hole_length > 0 and
				 * bimg_len < BLCKSZ if the HAS_HOLE flag is set.
				 */
				if ((blk->bimg_info & BKPIMAGE_HAS_HOLE) &&
					(blk->hole_offset == 0 ||
					 blk->hole_length == 0 ||
					 blk->bimg_len == BLCKSZ))
				{
					report_invalid_record(state,
										  "BKPIMAGE_HAS_HOLE set, but hole offset %u length %u block image length %u at %X/%X",
										  (unsigned int) blk->hole_offset,
										  (unsigned int) blk->hole_length,
										  (unsigned int) blk->bimg_len,
										  (uint32) (state->ReadRecPtr >> 32), (uint32) state->ReadRecPtr);
					goto err;
				}

				/*
				 * cross-check that hole_offset == 0 and hole_length == 0 if
				 * the HAS_HOLE flag is not set.
				 */
				if (!(blk->bimg_info & BKPIMAGE_HAS_HOLE) &&
					(blk->hole_offset != 0 || blk->hole_length != 0))
				{
					report_invalid_record(state,
										  "BKPIMAGE_HAS_HOLE not set, but hole offset %u length %u at %X/%X",
										  (unsigned int) blk->hole_offset,
										  (unsigned int) blk->hole_length,
										  (uint32) (state->ReadRecPtr >> 32), (uint32) state->ReadRecPtr);
					goto err;
				}

				/*
				 * cross-check that bimg_len < BLCKSZ if the IS_COMPRESSED
				 * flag is set.
				 */
				if ((blk->bimg_info & BKPIMAGE_IS_COMPRESSED) &&
					blk->bimg_len == BLCKSZ)
				{
					report_invalid_record(state,
										  "BKPIMAGE_IS_COMPRESSED set, but block image length %u at %X/%X",
										  (unsigned int) blk->bimg_len,
										  (uint32) (state->ReadRecPtr >> 32), (uint32) state->ReadRecPtr);
					goto err;
				}

				/*
				 * cross-check that bimg_len = BLCKSZ if neither HAS_HOLE nor
				 * IS_COMPRESSED flag is set.
				 */
				if (!(blk->bimg_info & BKPIMAGE_HAS_HOLE) &&
					!(blk->bimg_info & BKPIMAGE_IS_COMPRESSED) &&
					blk->bimg_len != BLCKSZ)
				{
					report_invalid_record(state,
										  "neither BKPIMAGE_HAS_HOLE nor BKPIMAGE_IS_COMPRESSED set, but block image length is %u at %X/%X",
										  (unsigned int) blk->data_len,
										  (uint32) (state->ReadRecPtr >> 32), (uint32) state->ReadRecPtr);
					goto err;
				}
			}
			if (!(fork_flags & BKPBLOCK_SAME_REL))
			{
				COPY_HEADER_FIELD(&blk->rnode, sizeof(RelFileNode));
				rnode = &blk->rnode;
			}
			else
			{
				if (rnode == NULL)
				{
					report_invalid_record(state,
										  "BKPBLOCK_SAME_REL set but no previous rel at %X/%X",
										  (uint32) (state->ReadRecPtr >> 32), (uint32) state->ReadRecPtr);
					goto err;
				}

				blk->rnode = *rnode;
			}
			COPY_HEADER_FIELD(&blk->blkno, sizeof(BlockNumber));
		}
		else
		{
			report_invalid_record(state,
								  "invalid block_id %u at %X/%X",
								  block_id,
								  (uint32) (state->ReadRecPtr >> 32),
								  (uint32) state->ReadRecPtr);
			goto err;
		}
	}

	if (remaining != datatotal)
		goto shortdata_err;

	/*
	 * Ok, we've parsed the fragment headers, and verified that the total
	 * length of the payload in the fragments is equal to the amount of data
	 * left. Copy the data of each fragment to a separate buffer.
	 *
	 * We could just set up pointers into readRecordBuf, but we want to align
	 * the data for the convenience of the callers. Backup images are not
	 * copied, however; they don't need alignment.
	 */

	/* block data first */
	for (block_id = 0; block_id <= state->max_block_id; block_id++)
	{
		DecodedBkpBlock *blk = &state->blocks[block_id];

		if (!blk->in_use)
			continue;

		Assert(blk->has_image || !blk->apply_image);

		if (blk->has_image)
		{
			blk->bkp_image = ptr;
			ptr += blk->bimg_len;
		}
		if (blk->has_data)
		{
			if (!blk->data || blk->data_len > blk->data_bufsz)
			{
				if (blk->data)
					pfree(blk->data);

				/*
				 * Force the initial request to be BLCKSZ so that we don't
				 * waste time with lots of trips through this stanza as a
				 * result of WAL compression.
				 */
				blk->data_bufsz = MAXALIGN(Max(blk->data_len, BLCKSZ));
				blk->data = palloc(blk->data_bufsz);
			}
			memcpy(blk->data, ptr, blk->data_len);
			ptr += blk->data_len;
		}
	}

	/* and finally, the main data */
	if (state->main_data_len > 0)
	{
		if (!state->main_data || state->main_data_len > state->main_data_bufsz)
		{
			if (state->main_data)
				pfree(state->main_data);

			/*
			 * main_data_bufsz must be MAXALIGN'ed.  In many xlog record
			 * types, we omit trailing struct padding on-disk to save a few
			 * bytes; but compilers may generate accesses to the xlog struct
			 * that assume that padding bytes are present.  If the palloc
			 * request is not large enough to include such padding bytes then
			 * we'll get valgrind complaints due to otherwise-harmless fetches
			 * of the padding bytes.
			 *
			 * In addition, force the initial request to be reasonably large
			 * so that we don't waste time with lots of trips through this
			 * stanza.  BLCKSZ / 2 seems like a good compromise choice.
			 */
			state->main_data_bufsz = MAXALIGN(Max(state->main_data_len,
												  BLCKSZ / 2));
			state->main_data = palloc(state->main_data_bufsz);
		}
		memcpy(state->main_data, ptr, state->main_data_len);
		ptr += state->main_data_len;
	}

	return true;

shortdata_err:
	report_invalid_record(state,
						  "record with invalid length at %X/%X",
						  (uint32) (state->ReadRecPtr >> 32), (uint32) state->ReadRecPtr);
err:
	*errormsg = state->errormsg_buf;

	return false;
}