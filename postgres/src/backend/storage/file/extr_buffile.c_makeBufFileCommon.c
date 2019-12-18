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
struct TYPE_3__ {int numFiles; int isInterXact; int dirty; long curOffset; scalar_t__ nbytes; scalar_t__ pos; scalar_t__ curFile; int /*<<< orphan*/  resowner; } ;
typedef  TYPE_1__ BufFile ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static BufFile *
makeBufFileCommon(int nfiles)
{
	BufFile    *file = (BufFile *) palloc(sizeof(BufFile));

	file->numFiles = nfiles;
	file->isInterXact = false;
	file->dirty = false;
	file->resowner = CurrentResourceOwner;
	file->curFile = 0;
	file->curOffset = 0L;
	file->pos = 0;
	file->nbytes = 0;

	return file;
}