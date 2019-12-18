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
typedef  int /*<<< orphan*/  offset ;
typedef  int /*<<< orphan*/  length ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  scalar_t__ Pointer ;
typedef  scalar_t__ OffsetNumber ;

/* Variables and functions */
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetDataLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 

void
generic_desc(StringInfo buf, XLogReaderState *record)
{
	Pointer		ptr = XLogRecGetData(record),
				end = ptr + XLogRecGetDataLen(record);

	while (ptr < end)
	{
		OffsetNumber offset,
					length;

		memcpy(&offset, ptr, sizeof(offset));
		ptr += sizeof(offset);
		memcpy(&length, ptr, sizeof(length));
		ptr += sizeof(length);
		ptr += length;

		if (ptr < end)
			appendStringInfo(buf, "offset %u, length %u; ", offset, length);
		else
			appendStringInfo(buf, "offset %u, length %u", offset, length);
	}

	return;
}