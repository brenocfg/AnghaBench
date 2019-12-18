#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  smgr_rnode; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (char*) ; 
 char* psprintf (char*,char*,scalar_t__) ; 
 char* relpath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
_mdfd_segpath(SMgrRelation reln, ForkNumber forknum, BlockNumber segno)
{
	char	   *path,
			   *fullpath;

	path = relpath(reln->smgr_rnode, forknum);

	if (segno > 0)
	{
		fullpath = psprintf("%s.%u", path, segno);
		pfree(path);
	}
	else
		fullpath = path;

	return fullpath;
}