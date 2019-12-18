#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ format; int /*<<< orphan*/  str; } ;
typedef  int ScanDirection ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ExplainState ;

/* Variables and functions */
#define  BackwardScanDirection 130 
 scalar_t__ EXPLAIN_FORMAT_TEXT ; 
 int /*<<< orphan*/  ExplainPropertyText (char*,char const*,TYPE_1__*) ; 
#define  ForwardScanDirection 129 
#define  NoMovementScanDirection 128 
 scalar_t__ ScanDirectionIsBackward (int) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 char* explain_get_index_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ExplainIndexScanDetails(Oid indexid, ScanDirection indexorderdir,
						ExplainState *es)
{
	const char *indexname = explain_get_index_name(indexid);

	if (es->format == EXPLAIN_FORMAT_TEXT)
	{
		if (ScanDirectionIsBackward(indexorderdir))
			appendStringInfoString(es->str, " Backward");
		appendStringInfo(es->str, " using %s", indexname);
	}
	else
	{
		const char *scandir;

		switch (indexorderdir)
		{
			case BackwardScanDirection:
				scandir = "Backward";
				break;
			case NoMovementScanDirection:
				scandir = "NoMovement";
				break;
			case ForwardScanDirection:
				scandir = "Forward";
				break;
			default:
				scandir = "???";
				break;
		}
		ExplainPropertyText("Scan Direction", scandir, es);
		ExplainPropertyText("Index Name", indexname, es);
	}
}