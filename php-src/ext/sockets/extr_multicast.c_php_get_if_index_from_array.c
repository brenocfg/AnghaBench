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
typedef  int /*<<< orphan*/  php_socket ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int SUCCESS ; 
 int php_get_if_index_from_zval (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_get_if_index_from_array(const HashTable *ht, const char *key,
	php_socket *sock, unsigned int *if_index)
{
	zval *val;

	if ((val = zend_hash_str_find(ht, key, strlen(key))) == NULL) {
		*if_index = 0; /* default: 0 */
		return SUCCESS;
	}

	return php_get_if_index_from_zval(val, if_index);
}