#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int segno; int /*<<< orphan*/  forknum; int /*<<< orphan*/  rnode; } ;
struct TYPE_5__ {int /*<<< orphan*/  mdfd_vfd; } ;
typedef  int /*<<< orphan*/  SMgrRelation ;
typedef  TYPE_1__ MdfdVec ;
typedef  TYPE_2__ FileTag ;
typedef  int BlockNumber ;

/* Variables and functions */
 int EXTENSION_DONT_CHECK_SIZE ; 
 int EXTENSION_RETURN_NULL ; 
 int FileSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBackendId ; 
 int /*<<< orphan*/  MAXPGPATH ; 
 scalar_t__ RELSEG_SIZE ; 
 int /*<<< orphan*/  WAIT_EVENT_DATA_FILE_SYNC ; 
 TYPE_1__* _mdfd_getseg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 char* _mdfd_segpath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  smgropen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 

int
mdsyncfiletag(const FileTag *ftag, char *path)
{
	SMgrRelation reln = smgropen(ftag->rnode, InvalidBackendId);
	MdfdVec    *v;
	char	   *p;

	/* Provide the path for informational messages. */
	p = _mdfd_segpath(reln, ftag->forknum, ftag->segno);
	strlcpy(path, p, MAXPGPATH);
	pfree(p);

	/* Try to open the requested segment. */
	v = _mdfd_getseg(reln,
					 ftag->forknum,
					 ftag->segno * (BlockNumber) RELSEG_SIZE,
					 false,
					 EXTENSION_RETURN_NULL | EXTENSION_DONT_CHECK_SIZE);
	if (v == NULL)
		return -1;

	/* Try to fsync the file. */
	return FileSync(v->mdfd_vfd, WAIT_EVENT_DATA_FILE_SYNC);
}