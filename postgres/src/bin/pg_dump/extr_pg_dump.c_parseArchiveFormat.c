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
typedef  int /*<<< orphan*/  ArchiveMode ;
typedef  int /*<<< orphan*/  ArchiveFormat ;

/* Variables and functions */
 int /*<<< orphan*/  archCustom ; 
 int /*<<< orphan*/  archDirectory ; 
 int /*<<< orphan*/  archModeAppend ; 
 int /*<<< orphan*/  archModeWrite ; 
 int /*<<< orphan*/  archNull ; 
 int /*<<< orphan*/  archTar ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 

__attribute__((used)) static ArchiveFormat
parseArchiveFormat(const char *format, ArchiveMode *mode)
{
	ArchiveFormat archiveFormat;

	*mode = archModeWrite;

	if (pg_strcasecmp(format, "a") == 0 || pg_strcasecmp(format, "append") == 0)
	{
		/* This is used by pg_dumpall, and is not documented */
		archiveFormat = archNull;
		*mode = archModeAppend;
	}
	else if (pg_strcasecmp(format, "c") == 0)
		archiveFormat = archCustom;
	else if (pg_strcasecmp(format, "custom") == 0)
		archiveFormat = archCustom;
	else if (pg_strcasecmp(format, "d") == 0)
		archiveFormat = archDirectory;
	else if (pg_strcasecmp(format, "directory") == 0)
		archiveFormat = archDirectory;
	else if (pg_strcasecmp(format, "p") == 0)
		archiveFormat = archNull;
	else if (pg_strcasecmp(format, "plain") == 0)
		archiveFormat = archNull;
	else if (pg_strcasecmp(format, "t") == 0)
		archiveFormat = archTar;
	else if (pg_strcasecmp(format, "tar") == 0)
		archiveFormat = archTar;
	else
		fatal("invalid output format \"%s\" specified", format);
	return archiveFormat;
}