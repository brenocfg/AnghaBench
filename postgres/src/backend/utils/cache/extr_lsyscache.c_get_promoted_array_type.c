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
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_array_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_element_type (int /*<<< orphan*/ ) ; 

Oid
get_promoted_array_type(Oid typid)
{
	Oid			array_type = get_array_type(typid);

	if (OidIsValid(array_type))
		return array_type;
	if (OidIsValid(get_element_type(typid)))
		return typid;
	return InvalidOid;
}