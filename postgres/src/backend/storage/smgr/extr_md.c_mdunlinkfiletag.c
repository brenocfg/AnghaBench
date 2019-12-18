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
struct TYPE_3__ {int /*<<< orphan*/  rnode; } ;
typedef  TYPE_1__ FileTag ;

/* Variables and functions */
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MAXPGPATH ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* relpathperm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int unlink (char*) ; 

int
mdunlinkfiletag(const FileTag *ftag, char *path)
{
	char	   *p;

	/* Compute the path. */
	p = relpathperm(ftag->rnode, MAIN_FORKNUM);
	strlcpy(path, p, MAXPGPATH);
	pfree(p);

	/* Try to unlink the file. */
	return unlink(path);
}