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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 char const* funcname_signature_string (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

const char *
func_signature_string(List *funcname, int nargs,
					  List *argnames, const Oid *argtypes)
{
	return funcname_signature_string(NameListToString(funcname),
									 nargs, argnames, argtypes);
}