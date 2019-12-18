#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ArchiveHandle ;
typedef  int /*<<< orphan*/  ArchiveFormat ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * _allocAH (char const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archModeRead ; 
 int /*<<< orphan*/  setupRestoreWorker ; 

Archive *
OpenArchive(const char *FileSpec, const ArchiveFormat fmt)
{
	ArchiveHandle *AH = _allocAH(FileSpec, fmt, 0, true, archModeRead, setupRestoreWorker);

	return (Archive *) AH;
}