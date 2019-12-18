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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_constant ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_execute_data ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  zend_constants ; 
 char* zend_get_executed_filename () ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_mangle_property_name (char const*,int,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_efree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_constant *zend_get_halt_offset_constant(const char *name, size_t name_len)
{
	zend_constant *c;
	static const char haltoff[] = "__COMPILER_HALT_OFFSET__";

	if (!EG(current_execute_data)) {
		return NULL;
	} else if (name_len == sizeof("__COMPILER_HALT_OFFSET__")-1 &&
	          !memcmp(name, "__COMPILER_HALT_OFFSET__", sizeof("__COMPILER_HALT_OFFSET__")-1)) {
		const char *cfilename;
		zend_string *haltname;
		size_t clen;

		cfilename = zend_get_executed_filename();
		clen = strlen(cfilename);
		/* check for __COMPILER_HALT_OFFSET__ */
		haltname = zend_mangle_property_name(haltoff,
			sizeof("__COMPILER_HALT_OFFSET__") - 1, cfilename, clen, 0);
		c = zend_hash_find_ptr(EG(zend_constants), haltname);
		zend_string_efree(haltname);
		return c;
	} else {
		return NULL;
	}
}