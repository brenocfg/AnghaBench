#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  fileName; } ;
typedef  size_t File ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_DB (int /*<<< orphan*/ ) ; 
 scalar_t__ FileAccess (size_t) ; 
 scalar_t__ FileIsNotOpen (size_t) ; 
 int /*<<< orphan*/  FileIsValid (size_t) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  SEEK_END ; 
 TYPE_1__* VfdCache ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

off_t
FileSize(File file)
{
	Assert(FileIsValid(file));

	DO_DB(elog(LOG, "FileSize %d (%s)",
			   file, VfdCache[file].fileName));

	if (FileIsNotOpen(file))
	{
		if (FileAccess(file) < 0)
			return (off_t) -1;
	}

	return lseek(VfdCache[file].fd, 0, SEEK_END);
}