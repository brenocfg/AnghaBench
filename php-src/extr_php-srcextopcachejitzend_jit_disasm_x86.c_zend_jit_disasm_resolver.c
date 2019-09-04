#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_uintptr_t ;
typedef  scalar_t__ uint64_t ;
struct ud {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {char const* dli_sname; void* dli_saddr; } ;
typedef  TYPE_1__ Dl_info ;

/* Variables and functions */
 scalar_t__ dladdr (void*,TYPE_1__*) ; 
 char* zend_jit_disasm_find_symbol (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char* zend_jit_disasm_resolver(struct ud *ud,
                                            uint64_t   addr,
                                            int64_t   *offset)
{
#ifndef _WIN32
	((void)ud);
	const char *name;
	void *a = (void*)(zend_uintptr_t)(addr);
	Dl_info info;

	name = zend_jit_disasm_find_symbol(addr, offset);
	if (name) {
		return name;
	}

	if (dladdr(a, &info)
	 && info.dli_sname != NULL
	 && info.dli_saddr == a) {
		return info.dli_sname;
	}
#else
	const char *name;
	name = zend_jit_disasm_find_symbol(addr, offset);
	if (name) {
		return name;
	}
#endif

	return NULL;
}