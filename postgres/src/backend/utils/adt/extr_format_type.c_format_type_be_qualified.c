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
 int /*<<< orphan*/  FORMAT_TYPE_FORCE_QUALIFY ; 
 char* format_type_extended (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

char *
format_type_be_qualified(Oid type_oid)
{
	return format_type_extended(type_oid, -1, FORMAT_TYPE_FORCE_QUALIFY);
}