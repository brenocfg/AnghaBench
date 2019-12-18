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
struct TYPE_2__ {int /*<<< orphan*/  message_size; scalar_t__ transactional; } ;
typedef  TYPE_1__ xl_logical_message ;
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 scalar_t__ XLOG_LOGICAL_MESSAGE ; 
 scalar_t__ XLR_INFO_MASK ; 
 char* XLogRecGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

void
logicalmsg_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	if (info == XLOG_LOGICAL_MESSAGE)
	{
		xl_logical_message *xlrec = (xl_logical_message *) rec;

		appendStringInfo(buf, "%s message size %zu bytes",
						 xlrec->transactional ? "transactional" : "nontransactional",
						 xlrec->message_size);
	}
}