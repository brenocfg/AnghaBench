#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  dataDumperArg; int /*<<< orphan*/  (* dataDumper ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_10__ {TYPE_1__* currToc; } ;
typedef  TYPE_2__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  _EndBlobs (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  _StartBlobs (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_PrintTocData(ArchiveHandle *AH, TocEntry *te)
{
	if (te->dataDumper)
	{
		AH->currToc = te;

		if (strcmp(te->desc, "BLOBS") == 0)
			_StartBlobs(AH, te);

		te->dataDumper((Archive *) AH, te->dataDumperArg);

		if (strcmp(te->desc, "BLOBS") == 0)
			_EndBlobs(AH, te);

		AH->currToc = NULL;
	}
}