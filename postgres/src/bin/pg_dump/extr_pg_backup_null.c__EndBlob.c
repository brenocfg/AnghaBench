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
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_4__ {int /*<<< orphan*/  WriteDataPtr; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  _WriteData ; 
 int /*<<< orphan*/  ahprintf (TYPE_1__*,char*) ; 

__attribute__((used)) static void
_EndBlob(ArchiveHandle *AH, TocEntry *te, Oid oid)
{
	AH->WriteDataPtr = _WriteData;

	ahprintf(AH, "SELECT pg_catalog.lo_close(0);\n\n");
}