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
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_10__ {scalar_t__ costs; } ;
struct TYPE_8__ {int /*<<< orphan*/  ss_currentRelation; } ;
struct TYPE_9__ {TYPE_1__ ss; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ ForeignScanState ;
typedef  TYPE_3__ ExplainState ;

/* Variables and functions */
 int /*<<< orphan*/  ExplainPropertyInteger (char*,char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ExplainPropertyText (char*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileGetOptions (int /*<<< orphan*/ ,char**,int*,int /*<<< orphan*/ **) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static void
fileExplainForeignScan(ForeignScanState *node, ExplainState *es)
{
	char	   *filename;
	bool		is_program;
	List	   *options;

	/* Fetch options --- we only need filename and is_program at this point */
	fileGetOptions(RelationGetRelid(node->ss.ss_currentRelation),
				   &filename, &is_program, &options);

	if (is_program)
		ExplainPropertyText("Foreign Program", filename, es);
	else
		ExplainPropertyText("Foreign File", filename, es);

	/* Suppress file size if we're not showing cost details */
	if (es->costs)
	{
		struct stat stat_buf;

		if (!is_program &&
			stat(filename, &stat_buf) == 0)
			ExplainPropertyInteger("Foreign File Size", "b",
								   (int64) stat_buf.st_size, es);
	}
}