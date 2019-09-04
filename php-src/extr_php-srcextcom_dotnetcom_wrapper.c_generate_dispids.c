#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_ulong ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {int /*<<< orphan*/ * name_to_dispid; int /*<<< orphan*/ * dispid_to_name; int /*<<< orphan*/  object; } ;
typedef  TYPE_1__ php_dispatchex ;
typedef  int /*<<< orphan*/  namebuf ;
struct TYPE_5__ {int /*<<< orphan*/  function_table; } ;
typedef  int /*<<< orphan*/  HashPosition ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (int /*<<< orphan*/ *) ; 
 int HASH_KEY_IS_LONG ; 
 int HASH_KEY_NON_EXISTENT ; 
 char* ZEND_ULONG_FMT ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZVAL_PTR_DTOR ; 
 int /*<<< orphan*/  ZVAL_STR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* Z_OBJCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Z_OBJPROP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_hash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_hash_get_current_key_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_index_update (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_internal_pointer_reset_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_move_forward_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_hash_next_free_element (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generate_dispids(php_dispatchex *disp)
{
	HashPosition pos;
	zend_string *name = NULL;
	zval *tmp, tmp2;
	int keytype;
	zend_ulong pid;

	if (disp->dispid_to_name == NULL) {
		ALLOC_HASHTABLE(disp->dispid_to_name);
		ALLOC_HASHTABLE(disp->name_to_dispid);
		zend_hash_init(disp->name_to_dispid, 0, NULL, ZVAL_PTR_DTOR, 0);
		zend_hash_init(disp->dispid_to_name, 0, NULL, ZVAL_PTR_DTOR, 0);
	}

	/* properties */
	if (Z_OBJPROP(disp->object)) {
		zend_hash_internal_pointer_reset_ex(Z_OBJPROP(disp->object), &pos);
		while (HASH_KEY_NON_EXISTENT != (keytype =
				zend_hash_get_current_key_ex(Z_OBJPROP(disp->object), &name,
				&pid, &pos))) {
			char namebuf[32];
			if (keytype == HASH_KEY_IS_LONG) {
				snprintf(namebuf, sizeof(namebuf), ZEND_ULONG_FMT, pid);
				name = zend_string_init(namebuf, strlen(namebuf), 0);
			} else {
				zend_string_addref(name);
			}

			zend_hash_move_forward_ex(Z_OBJPROP(disp->object), &pos);

			/* Find the existing id */
			if ((tmp = zend_hash_find(disp->name_to_dispid, name)) != NULL) {
				zend_string_release_ex(name, 0);
				continue;
			}

			/* add the mappings */
			ZVAL_STR_COPY(&tmp2, name);
			pid = zend_hash_next_free_element(disp->dispid_to_name);
			zend_hash_index_update(disp->dispid_to_name, pid, &tmp2);

			ZVAL_LONG(&tmp2, pid);
			zend_hash_update(disp->name_to_dispid, name, &tmp2);

			zend_string_release_ex(name, 0);
		}
	}

	/* functions */
	if (Z_OBJCE(disp->object)) {
		zend_hash_internal_pointer_reset_ex(&Z_OBJCE(disp->object)->function_table, &pos);
		while (HASH_KEY_NON_EXISTENT != (keytype =
				zend_hash_get_current_key_ex(&Z_OBJCE(disp->object)->function_table,
			 	&name, &pid, &pos))) {

			char namebuf[32];
			if (keytype == HASH_KEY_IS_LONG) {
				snprintf(namebuf, sizeof(namebuf), "%d", pid);
				name = zend_string_init(namebuf, strlen(namebuf), 0);
			} else {
				zend_string_addref(name);
			}

			zend_hash_move_forward_ex(&Z_OBJCE(disp->object)->function_table, &pos);

			/* Find the existing id */
			if ((tmp = zend_hash_find(disp->name_to_dispid, name)) != NULL) {
				zend_string_release_ex(name, 0);
				continue;
			}

			/* add the mappings */
			ZVAL_STR_COPY(&tmp2, name);
			pid = zend_hash_next_free_element(disp->dispid_to_name);
			zend_hash_index_update(disp->dispid_to_name, pid, &tmp2);

			ZVAL_LONG(&tmp2, pid);
			zend_hash_update(disp->name_to_dispid, name, &tmp2);

			zend_string_release_ex(name, 0);
		}
	}
}