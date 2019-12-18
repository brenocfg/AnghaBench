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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  bits16 ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  FORMAT_TYPE_FORCE_QUALIFY ; 
 int /*<<< orphan*/  FORMAT_TYPE_TYPEMOD_GIVEN ; 
 char* format_type_extended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_builtin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
deparse_type_name(Oid type_oid, int32 typemod)
{
	bits16		flags = FORMAT_TYPE_TYPEMOD_GIVEN;

	if (!is_builtin(type_oid))
		flags |= FORMAT_TYPE_FORCE_QUALIFY;

	return format_type_extended(type_oid, typemod, flags);
}