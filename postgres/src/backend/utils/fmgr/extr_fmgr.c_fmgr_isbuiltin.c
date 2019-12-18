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
typedef  size_t uint16 ;
typedef  size_t Oid ;
typedef  int /*<<< orphan*/  FmgrBuiltin ;

/* Variables and functions */
 size_t InvalidOidBuiltinMapping ; 
 size_t* fmgr_builtin_oid_index ; 
 int /*<<< orphan*/  const* fmgr_builtins ; 
 size_t fmgr_last_builtin_oid ; 

__attribute__((used)) static const FmgrBuiltin *
fmgr_isbuiltin(Oid id)
{
	uint16		index;

	/* fast lookup only possible if original oid still assigned */
	if (id > fmgr_last_builtin_oid)
		return NULL;

	/*
	 * Lookup function data. If there's a miss in that range it's likely a
	 * nonexistent function, returning NULL here will trigger an ERROR later.
	 */
	index = fmgr_builtin_oid_index[id];
	if (index == InvalidOidBuiltinMapping)
		return NULL;

	return &fmgr_builtins[index];
}