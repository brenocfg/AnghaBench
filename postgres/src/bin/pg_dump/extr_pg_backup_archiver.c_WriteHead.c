#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct tm {int /*<<< orphan*/  tm_isdst; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct TYPE_13__ {int /*<<< orphan*/  remoteVersionStr; } ;
struct TYPE_14__ {TYPE_1__ public; int /*<<< orphan*/  connection; int /*<<< orphan*/  createDate; int /*<<< orphan*/  compression; int /*<<< orphan*/  format; int /*<<< orphan*/  (* WriteBytePtr ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  offSize; int /*<<< orphan*/  intSize; int /*<<< orphan*/  version; int /*<<< orphan*/  (* WriteBufPtr ) (TYPE_2__*,char*,int) ;} ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARCHIVE_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARCHIVE_REV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_VERSION ; 
 int /*<<< orphan*/  PQdb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteInt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteStr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
WriteHead(ArchiveHandle *AH)
{
	struct tm	crtm;

	AH->WriteBufPtr(AH, "PGDMP", 5);	/* Magic code */
	AH->WriteBytePtr(AH, ARCHIVE_MAJOR(AH->version));
	AH->WriteBytePtr(AH, ARCHIVE_MINOR(AH->version));
	AH->WriteBytePtr(AH, ARCHIVE_REV(AH->version));
	AH->WriteBytePtr(AH, AH->intSize);
	AH->WriteBytePtr(AH, AH->offSize);
	AH->WriteBytePtr(AH, AH->format);
	WriteInt(AH, AH->compression);
	crtm = *localtime(&AH->createDate);
	WriteInt(AH, crtm.tm_sec);
	WriteInt(AH, crtm.tm_min);
	WriteInt(AH, crtm.tm_hour);
	WriteInt(AH, crtm.tm_mday);
	WriteInt(AH, crtm.tm_mon);
	WriteInt(AH, crtm.tm_year);
	WriteInt(AH, crtm.tm_isdst);
	WriteStr(AH, PQdb(AH->connection));
	WriteStr(AH, AH->public.remoteVersionStr);
	WriteStr(AH, PG_VERSION);
}