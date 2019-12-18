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
struct TYPE_2__ {int /*<<< orphan*/  connection; } ;
typedef  TYPE_1__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 char* PQparameterStatus (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bool
is_superuser(Archive *fout)
{
	ArchiveHandle *AH = (ArchiveHandle *) fout;
	const char *val;

	val = PQparameterStatus(AH->connection, "is_superuser");

	if (val && strcmp(val, "on") == 0)
		return true;

	return false;
}