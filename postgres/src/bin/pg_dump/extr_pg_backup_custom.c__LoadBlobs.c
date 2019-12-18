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
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  EndRestoreBlob (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  EndRestoreBlobs (int /*<<< orphan*/ *) ; 
 scalar_t__ ReadInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StartRestoreBlob (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  StartRestoreBlobs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _PrintData (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_LoadBlobs(ArchiveHandle *AH, bool drop)
{
	Oid			oid;

	StartRestoreBlobs(AH);

	oid = ReadInt(AH);
	while (oid != 0)
	{
		StartRestoreBlob(AH, oid, drop);
		_PrintData(AH);
		EndRestoreBlob(AH, oid);
		oid = ReadInt(AH);
	}

	EndRestoreBlobs(AH);
}