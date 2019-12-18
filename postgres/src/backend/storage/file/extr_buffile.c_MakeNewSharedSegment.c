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
struct TYPE_3__ {int /*<<< orphan*/  fileset; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ File ;
typedef  TYPE_1__ BufFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int MAXPGPATH ; 
 scalar_t__ SharedFileSetCreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SharedFileSetDelete (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SharedSegmentName (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static File
MakeNewSharedSegment(BufFile *buffile, int segment)
{
	char		name[MAXPGPATH];
	File		file;

	/*
	 * It is possible that there are files left over from before a crash
	 * restart with the same name.  In order for BufFileOpenShared() not to
	 * get confused about how many segments there are, we'll unlink the next
	 * segment number if it already exists.
	 */
	SharedSegmentName(name, buffile->name, segment + 1);
	SharedFileSetDelete(buffile->fileset, name, true);

	/* Create the new segment. */
	SharedSegmentName(name, buffile->name, segment);
	file = SharedFileSetCreate(buffile->fileset, name);

	/* SharedFileSetCreate would've errored out */
	Assert(file > 0);

	return file;
}