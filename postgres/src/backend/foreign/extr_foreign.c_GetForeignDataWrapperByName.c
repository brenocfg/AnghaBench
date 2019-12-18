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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ForeignDataWrapper ;

/* Variables and functions */
 int /*<<< orphan*/ * GetForeignDataWrapper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_foreign_data_wrapper_oid (char const*,int) ; 

ForeignDataWrapper *
GetForeignDataWrapperByName(const char *fdwname, bool missing_ok)
{
	Oid			fdwId = get_foreign_data_wrapper_oid(fdwname, missing_ok);

	if (!OidIsValid(fdwId))
		return NULL;

	return GetForeignDataWrapper(fdwId);
}