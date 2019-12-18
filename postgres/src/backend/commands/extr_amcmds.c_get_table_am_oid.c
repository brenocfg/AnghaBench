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
 int /*<<< orphan*/  AMTYPE_TABLE ; 
 int /*<<< orphan*/  get_am_type_oid (char const*,int /*<<< orphan*/ ,int) ; 

Oid
get_table_am_oid(const char *amname, bool missing_ok)
{
	return get_am_type_oid(amname, AMTYPE_TABLE, missing_ok);
}