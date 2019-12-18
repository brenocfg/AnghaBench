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
typedef  int /*<<< orphan*/  SetupWorkerPtrType ;
typedef  int /*<<< orphan*/  ArchiveMode ;
typedef  int /*<<< orphan*/  ArchiveHandle ;
typedef  int /*<<< orphan*/  ArchiveFormat ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * _allocAH (char const*,int /*<<< orphan*/  const,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Archive *
CreateArchive(const char *FileSpec, const ArchiveFormat fmt,
			  const int compression, bool dosync, ArchiveMode mode,
			  SetupWorkerPtrType setupDumpWorker)

{
	ArchiveHandle *AH = _allocAH(FileSpec, fmt, compression, dosync,
								 mode, setupDumpWorker);

	return (Archive *) AH;
}