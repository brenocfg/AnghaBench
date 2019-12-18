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
typedef  int /*<<< orphan*/  relopt_gen ;
typedef  int /*<<< orphan*/  relopt_enum_elt_def ;
struct TYPE_2__ {int default_val; char const* detailmsg; int /*<<< orphan*/ * members; } ;
typedef  TYPE_1__ relopt_enum ;
typedef  int /*<<< orphan*/  bits32 ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  RELOPT_TYPE_ENUM ; 
 int /*<<< orphan*/  add_reloption (int /*<<< orphan*/ *) ; 
 scalar_t__ allocate_reloption (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 

void
add_enum_reloption(bits32 kinds, const char *name, const char *desc,
				   relopt_enum_elt_def *members, int default_val,
				   const char *detailmsg, LOCKMODE lockmode)
{
	relopt_enum *newoption;

	newoption = (relopt_enum *) allocate_reloption(kinds, RELOPT_TYPE_ENUM,
												   name, desc, lockmode);
	newoption->members = members;
	newoption->default_val = default_val;
	newoption->detailmsg = detailmsg;

	add_reloption((relopt_gen *) newoption);
}