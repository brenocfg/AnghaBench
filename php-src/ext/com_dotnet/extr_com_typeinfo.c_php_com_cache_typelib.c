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
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  ITypeLib ;

/* Variables and functions */
 int /*<<< orphan*/  php_com_typelibraries ; 
 int /*<<< orphan*/  php_com_typelibraries_mutex ; 
 int /*<<< orphan*/  tsrm_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsrm_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_str_add_ptr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ITypeLib *php_com_cache_typelib(ITypeLib* TL, char *cache_key, zend_long cache_key_len) {
	ITypeLib* result;
#ifdef ZTS
	tsrm_mutex_lock(php_com_typelibraries_mutex);
#endif

	result = zend_hash_str_add_ptr(&php_com_typelibraries, cache_key, cache_key_len, TL);

#ifdef ZTS
	tsrm_mutex_unlock(php_com_typelibraries_mutex);
#endif

	return result;
}