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
 scalar_t__ TYPTYPE_ENUM ; 
 scalar_t__ get_typtype (int /*<<< orphan*/ ) ; 

bool
type_is_enum(Oid typid)
{
	return (get_typtype(typid) == TYPTYPE_ENUM);
}