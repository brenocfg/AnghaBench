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
struct TYPE_4__ {long numFiles; int readOnly; scalar_t__ resowner; int /*<<< orphan*/ * files; int /*<<< orphan*/ * fileset; int /*<<< orphan*/  dirty; } ;
typedef  int /*<<< orphan*/  File ;
typedef  TYPE_1__ BufFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 long BUFFILE_SEG_SIZE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 

long
BufFileAppend(BufFile *target, BufFile *source)
{
	long		startBlock = target->numFiles * BUFFILE_SEG_SIZE;
	int			newNumFiles = target->numFiles + source->numFiles;
	int			i;

	Assert(target->fileset != NULL);
	Assert(source->readOnly);
	Assert(!source->dirty);
	Assert(source->fileset != NULL);

	if (target->resowner != source->resowner)
		elog(ERROR, "could not append BufFile with non-matching resource owner");

	target->files = (File *)
		repalloc(target->files, sizeof(File) * newNumFiles);
	for (i = target->numFiles; i < newNumFiles; i++)
		target->files[i] = source->files[i - target->numFiles];
	target->numFiles = newNumFiles;

	return startBlock;
}