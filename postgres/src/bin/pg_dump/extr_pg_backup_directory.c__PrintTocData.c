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
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ lclTocEntry ;
struct TYPE_5__ {int /*<<< orphan*/  desc; scalar_t__ formatData; } ;
typedef  TYPE_2__ TocEntry ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  _LoadBlobs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _PrintFileData (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  setFilePath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
_PrintTocData(ArchiveHandle *AH, TocEntry *te)
{
	lclTocEntry *tctx = (lclTocEntry *) te->formatData;

	if (!tctx->filename)
		return;

	if (strcmp(te->desc, "BLOBS") == 0)
		_LoadBlobs(AH);
	else
	{
		char		fname[MAXPGPATH];

		setFilePath(AH, fname, tctx->filename);
		_PrintFileData(AH, fname);
	}
}