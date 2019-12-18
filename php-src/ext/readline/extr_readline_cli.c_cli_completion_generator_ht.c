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
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ SUCCESS ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,size_t) ; 
 void* zend_hash_get_current_data_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_get_current_key (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_hash_has_more_elements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_internal_pointer_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_hash_move_forward (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *cli_completion_generator_ht(const char *text, size_t textlen, int *state, HashTable *ht, void **pData) /* {{{ */
{
	zend_string *name;
	zend_ulong number;

	if (!(*state % 2)) {
		zend_hash_internal_pointer_reset(ht);
		(*state)++;
	}
	while(zend_hash_has_more_elements(ht) == SUCCESS) {
		zend_hash_get_current_key(ht, &name, &number);
		if (!textlen || !strncmp(ZSTR_VAL(name), text, textlen)) {
			if (pData) {
				*pData = zend_hash_get_current_data_ptr(ht);
			}
			zend_hash_move_forward(ht);
			return ZSTR_VAL(name);
		}
		if (zend_hash_move_forward(ht) == FAILURE) {
			break;
		}
	}
	(*state)++;
	return NULL;
}