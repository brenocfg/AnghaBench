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
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char*,char) ; 
 void* zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void* schema_find_by_ref(HashTable *ht, char *ref)
{
	void *tmp;

	if ((tmp = zend_hash_str_find_ptr(ht, ref, strlen(ref))) != NULL) {
		return tmp;
	} else {
		ref = strrchr(ref, ':');
		if (ref) {
			if ((tmp = zend_hash_str_find_ptr(ht, ref, strlen(ref))) != NULL) {
				return tmp;
			}
		}
	}
	return NULL;
}