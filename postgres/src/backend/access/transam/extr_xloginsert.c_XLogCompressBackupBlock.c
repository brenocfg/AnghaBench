#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16 ;
typedef  scalar_t__ int32 ;
struct TYPE_2__ {char* data; } ;
typedef  TYPE_1__ PGAlignedBlock ;

/* Variables and functions */
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  PGLZ_strategy_default ; 
 scalar_t__ SizeOfXLogRecordBlockCompressHeader ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 scalar_t__ pglz_compress (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
XLogCompressBackupBlock(char *page, uint16 hole_offset, uint16 hole_length,
						char *dest, uint16 *dlen)
{
	int32		orig_len = BLCKSZ - hole_length;
	int32		len;
	int32		extra_bytes = 0;
	char	   *source;
	PGAlignedBlock tmp;

	if (hole_length != 0)
	{
		/* must skip the hole */
		source = tmp.data;
		memcpy(source, page, hole_offset);
		memcpy(source + hole_offset,
			   page + (hole_offset + hole_length),
			   BLCKSZ - (hole_length + hole_offset));

		/*
		 * Extra data needs to be stored in WAL record for the compressed
		 * version of block image if the hole exists.
		 */
		extra_bytes = SizeOfXLogRecordBlockCompressHeader;
	}
	else
		source = page;

	/*
	 * We recheck the actual size even if pglz_compress() reports success and
	 * see if the number of bytes saved by compression is larger than the
	 * length of extra data needed for the compressed version of block image.
	 */
	len = pglz_compress(source, orig_len, dest, PGLZ_strategy_default);
	if (len >= 0 &&
		len + extra_bytes < orig_len)
	{
		*dlen = (uint16) len;	/* successful compression */
		return true;
	}
	return false;
}