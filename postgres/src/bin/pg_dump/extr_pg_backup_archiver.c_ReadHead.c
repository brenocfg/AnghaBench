#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {void* tm_isdst; void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct TYPE_13__ {char (* ReadBytePtr ) (TYPE_1__*) ;scalar_t__ version; char intSize; char offSize; int format; int compression; void* archiveDumpVersion; void* archiveRemoteVersion; int /*<<< orphan*/  createDate; void* archdbname; int /*<<< orphan*/  (* ReadBufPtr ) (TYPE_1__*,char*,int) ;int /*<<< orphan*/  readHeader; } ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ K_VERS_1_0 ; 
 scalar_t__ K_VERS_1_10 ; 
 scalar_t__ K_VERS_1_2 ; 
 scalar_t__ K_VERS_1_4 ; 
 scalar_t__ K_VERS_1_7 ; 
 scalar_t__ K_VERS_MAX ; 
 scalar_t__ MAKE_ARCHIVE_VERSION (char,char,char) ; 
 void* ReadInt (TYPE_1__*) ; 
 void* ReadStr (TYPE_1__*) ; 
 int Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  mktime (struct tm*) ; 
 int /*<<< orphan*/  pg_log_warning (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,int) ; 
 char stub2 (TYPE_1__*) ; 
 char stub3 (TYPE_1__*) ; 
 char stub4 (TYPE_1__*) ; 
 char stub5 (TYPE_1__*) ; 
 char stub6 (TYPE_1__*) ; 
 int stub7 (TYPE_1__*) ; 
 int stub8 (TYPE_1__*) ; 

void
ReadHead(ArchiveHandle *AH)
{
	char		tmpMag[7];
	int			fmt;
	struct tm	crtm;

	/*
	 * If we haven't already read the header, do so.
	 *
	 * NB: this code must agree with _discoverArchiveFormat().  Maybe find a
	 * way to unify the cases?
	 */
	if (!AH->readHeader)
	{
		char		vmaj,
					vmin,
					vrev;

		AH->ReadBufPtr(AH, tmpMag, 5);

		if (strncmp(tmpMag, "PGDMP", 5) != 0)
			fatal("did not find magic string in file header");

		vmaj = AH->ReadBytePtr(AH);
		vmin = AH->ReadBytePtr(AH);

		if (vmaj > 1 || (vmaj == 1 && vmin > 0))	/* Version > 1.0 */
			vrev = AH->ReadBytePtr(AH);
		else
			vrev = 0;

		AH->version = MAKE_ARCHIVE_VERSION(vmaj, vmin, vrev);

		if (AH->version < K_VERS_1_0 || AH->version > K_VERS_MAX)
			fatal("unsupported version (%d.%d) in file header",
				  vmaj, vmin);

		AH->intSize = AH->ReadBytePtr(AH);
		if (AH->intSize > 32)
			fatal("sanity check on integer size (%lu) failed",
				  (unsigned long) AH->intSize);

		if (AH->intSize > sizeof(int))
			pg_log_warning("archive was made on a machine with larger integers, some operations might fail");

		if (AH->version >= K_VERS_1_7)
			AH->offSize = AH->ReadBytePtr(AH);
		else
			AH->offSize = AH->intSize;

		fmt = AH->ReadBytePtr(AH);

		if (AH->format != fmt)
			fatal("expected format (%d) differs from format found in file (%d)",
				  AH->format, fmt);
	}

	if (AH->version >= K_VERS_1_2)
	{
		if (AH->version < K_VERS_1_4)
			AH->compression = AH->ReadBytePtr(AH);
		else
			AH->compression = ReadInt(AH);
	}
	else
		AH->compression = Z_DEFAULT_COMPRESSION;

#ifndef HAVE_LIBZ
	if (AH->compression != 0)
		pg_log_warning("archive is compressed, but this installation does not support compression -- no data will be available");
#endif

	if (AH->version >= K_VERS_1_4)
	{
		crtm.tm_sec = ReadInt(AH);
		crtm.tm_min = ReadInt(AH);
		crtm.tm_hour = ReadInt(AH);
		crtm.tm_mday = ReadInt(AH);
		crtm.tm_mon = ReadInt(AH);
		crtm.tm_year = ReadInt(AH);
		crtm.tm_isdst = ReadInt(AH);

		AH->archdbname = ReadStr(AH);

		AH->createDate = mktime(&crtm);

		if (AH->createDate == (time_t) -1)
			pg_log_warning("invalid creation date in header");
	}

	if (AH->version >= K_VERS_1_10)
	{
		AH->archiveRemoteVersion = ReadStr(AH);
		AH->archiveDumpVersion = ReadStr(AH);
	}
}