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
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  ExecuteSqlCommand (int /*<<< orphan*/ *,char*,char*) ; 

void
CommitTransaction(Archive *AHX)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;

	ExecuteSqlCommand(AH, "COMMIT", "could not commit database transaction");
}