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
typedef  int /*<<< orphan*/  ForeignServer ;

/* Variables and functions */
 int /*<<< orphan*/ * GetForeignServer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_foreign_server_oid (char const*,int) ; 

ForeignServer *
GetForeignServerByName(const char *srvname, bool missing_ok)
{
	Oid			serverid = get_foreign_server_oid(srvname, missing_ok);

	if (!OidIsValid(serverid))
		return NULL;

	return GetForeignServer(serverid);
}