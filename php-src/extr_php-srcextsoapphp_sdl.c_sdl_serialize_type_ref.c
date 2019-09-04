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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  smart_str ;
typedef  scalar_t__ sdlTypePtr ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  WSDL_CACHE_PUT_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void sdl_serialize_type_ref(sdlTypePtr type, HashTable *tmp_types, smart_str *out) {
	if (type) {
		zval *type_num;
		if ((type_num = zend_hash_str_find(tmp_types, (char*)&type, sizeof(type))) != NULL) {
			WSDL_CACHE_PUT_INT(Z_LVAL_P(type_num), out);
		} else {
			WSDL_CACHE_PUT_INT(0, out);
		}
	} else {
		WSDL_CACHE_PUT_INT(0,out);
	}
}