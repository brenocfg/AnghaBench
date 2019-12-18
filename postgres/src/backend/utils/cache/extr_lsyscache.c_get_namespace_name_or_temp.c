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

/* Variables and functions */
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 scalar_t__ isTempNamespace (int /*<<< orphan*/ ) ; 

char *
get_namespace_name_or_temp(Oid nspid)
{
	if (isTempNamespace(nspid))
		return "pg_temp";
	else
		return get_namespace_name(nspid);
}