#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_12__ {scalar_t__ nNumOfElements; } ;
typedef  TYPE_1__ HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (TYPE_1__*) ; 
 scalar_t__ FAILURE ; 
 scalar_t__ HASH_KEY_NON_EXISTENT ; 
 scalar_t__ SUCCESS ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 scalar_t__ memchr (char*,char,size_t) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  phar_add_empty (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  phar_compare_dir_name ; 
 int /*<<< orphan*/  phar_dir_ops ; 
 int /*<<< orphan*/ * php_stream_alloc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ safe_emalloc (size_t,int,int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,size_t) ; 
 scalar_t__ zend_hash_get_current_key (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_hash_has_more_elements (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_init (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_internal_pointer_reset (TYPE_1__*) ; 
 scalar_t__ zend_hash_move_forward (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_sort (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static php_stream *phar_make_dirstream(char *dir, HashTable *manifest) /* {{{ */
{
	HashTable *data;
	size_t dirlen = strlen(dir);
	char *entry, *found, *save;
	zend_string *str_key;
	size_t keylen;
	zend_ulong unused;

	ALLOC_HASHTABLE(data);
	zend_hash_init(data, 64, NULL, NULL, 0);

	if ((*dir == '/' && dirlen == 1 && (manifest->nNumOfElements == 0)) || (dirlen >= sizeof(".phar")-1 && !memcmp(dir, ".phar", sizeof(".phar")-1))) {
		/* make empty root directory for empty phar */
		/* make empty directory for .phar magic directory */
		efree(dir);
		return php_stream_alloc(&phar_dir_ops, data, NULL, "r");
	}

	zend_hash_internal_pointer_reset(manifest);

	while (FAILURE != zend_hash_has_more_elements(manifest)) {
		if (HASH_KEY_NON_EXISTENT == zend_hash_get_current_key(manifest, &str_key, &unused)) {
			break;
		}

		keylen = ZSTR_LEN(str_key);
		if (keylen <= dirlen) {
			if (keylen == 0 || keylen < dirlen || !strncmp(ZSTR_VAL(str_key), dir, dirlen)) {
				if (SUCCESS != zend_hash_move_forward(manifest)) {
					break;
				}
				continue;
			}
		}

		if (*dir == '/') {
			/* root directory */
			if (keylen >= sizeof(".phar")-1 && !memcmp(ZSTR_VAL(str_key), ".phar", sizeof(".phar")-1)) {
				/* do not add any magic entries to this directory */
				if (SUCCESS != zend_hash_move_forward(manifest)) {
					break;
				}
				continue;
			}

			if (NULL != (found = (char *) memchr(ZSTR_VAL(str_key), '/', keylen))) {
				/* the entry has a path separator and is a subdirectory */
				entry = (char *) safe_emalloc(found - ZSTR_VAL(str_key), 1, 1);
				memcpy(entry, ZSTR_VAL(str_key), found - ZSTR_VAL(str_key));
				keylen = found - ZSTR_VAL(str_key);
				entry[keylen] = '\0';
			} else {
				entry = (char *) safe_emalloc(keylen, 1, 1);
				memcpy(entry, ZSTR_VAL(str_key), keylen);
				entry[keylen] = '\0';
			}

			goto PHAR_ADD_ENTRY;
		} else {
			if (0 != memcmp(ZSTR_VAL(str_key), dir, dirlen)) {
				/* entry in directory not found */
				if (SUCCESS != zend_hash_move_forward(manifest)) {
					break;
				}
				continue;
			} else {
				if (ZSTR_VAL(str_key)[dirlen] != '/') {
					if (SUCCESS != zend_hash_move_forward(manifest)) {
						break;
					}
					continue;
				}
			}
		}

		save = ZSTR_VAL(str_key);
		save += dirlen + 1; /* seek to just past the path separator */

		if (NULL != (found = (char *) memchr(save, '/', keylen - dirlen - 1))) {
			/* is subdirectory */
			save -= dirlen + 1;
			entry = (char *) safe_emalloc(found - save + dirlen, 1, 1);
			memcpy(entry, save + dirlen + 1, found - save - dirlen - 1);
			keylen = found - save - dirlen - 1;
			entry[keylen] = '\0';
		} else {
			/* is file */
			save -= dirlen + 1;
			entry = (char *) safe_emalloc(keylen - dirlen, 1, 1);
			memcpy(entry, save + dirlen + 1, keylen - dirlen - 1);
			entry[keylen - dirlen - 1] = '\0';
			keylen = keylen - dirlen - 1;
		}
PHAR_ADD_ENTRY:
		if (keylen) {
			phar_add_empty(data, entry, keylen);
		}

		efree(entry);

		if (SUCCESS != zend_hash_move_forward(manifest)) {
			break;
		}
	}

	if (FAILURE != zend_hash_has_more_elements(data)) {
		efree(dir);
		zend_hash_sort(data, phar_compare_dir_name, 0);
		return php_stream_alloc(&phar_dir_ops, data, NULL, "r");
	} else {
		efree(dir);
		return php_stream_alloc(&phar_dir_ops, data, NULL, "r");
	}
}