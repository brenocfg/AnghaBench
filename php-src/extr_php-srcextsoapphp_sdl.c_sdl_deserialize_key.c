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
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  WSDL_CACHE_GET_INT (int,char**) ; 
 int /*<<< orphan*/  WSDL_CACHE_SKIP (int,char**) ; 
 int WSDL_NO_STRING_MARKER ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zend_hash_str_add_ptr (int /*<<< orphan*/ *,char*,int,void*) ; 

__attribute__((used)) static void sdl_deserialize_key(HashTable* ht, void* data, char **in)
{
	int len;

	WSDL_CACHE_GET_INT(len, in);
	if (len == WSDL_NO_STRING_MARKER) {
		zend_hash_next_index_insert_ptr(ht, data);
	} else {
		zend_hash_str_add_ptr(ht, *in, len, data);
		WSDL_CACHE_SKIP(len, in);
	}
}