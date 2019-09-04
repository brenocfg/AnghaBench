#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  TYPE_1__* sdlTypePtr ;
struct TYPE_13__ {int /*<<< orphan*/ * attributeGroups; } ;
typedef  TYPE_2__ sdlCtx ;
typedef  TYPE_3__* sdlAttributePtr ;
typedef  int /*<<< orphan*/  sdlAttribute ;
struct TYPE_14__ {int /*<<< orphan*/ * ref; int /*<<< orphan*/ * extraAttributes; void* name; void* namens; void* fixed; void* def; } ;
struct TYPE_12__ {scalar_t__ attributes; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ HASH_KEY_IS_STRING ; 
 int /*<<< orphan*/  copy_extra_attribute ; 
 int /*<<< orphan*/  delete_extra_attribute ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 void* emalloc (int) ; 
 void* estrdup (void*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  schema_attribute_fixup (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ schema_find_by_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_add_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_hash_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* zend_hash_get_current_data_ptr (scalar_t__) ; 
 int /*<<< orphan*/  zend_hash_get_current_key (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_hash_get_current_key_type (scalar_t__) ; 
 int /*<<< orphan*/  zend_hash_index_del (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_internal_pointer_reset (scalar_t__) ; 
 int /*<<< orphan*/  zend_hash_move_forward (scalar_t__) ; 
 int /*<<< orphan*/  zend_hash_num_elements (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void schema_attributegroup_fixup(sdlCtx *ctx, sdlAttributePtr attr, HashTable *ht)
{
	sdlTypePtr tmp;
	sdlAttributePtr tmp_attr;

	if (attr->ref != NULL) {
		if (ctx->attributeGroups != NULL) {
			tmp = (sdlTypePtr)schema_find_by_ref(ctx->attributeGroups, attr->ref);
			if (tmp) {
				if (tmp->attributes) {
					zend_hash_internal_pointer_reset(tmp->attributes);
					while ((tmp_attr = zend_hash_get_current_data_ptr(tmp->attributes)) != NULL) {
						if (zend_hash_get_current_key_type(tmp->attributes) == HASH_KEY_IS_STRING) {
							zend_string* _key;
							sdlAttributePtr newAttr;

							schema_attribute_fixup(ctx, tmp_attr);

							newAttr = emalloc(sizeof(sdlAttribute));
							memcpy(newAttr, tmp_attr, sizeof(sdlAttribute));
							if (newAttr->def) {newAttr->def = estrdup(newAttr->def);}
							if (newAttr->fixed) {newAttr->fixed = estrdup(newAttr->fixed);}
							if (newAttr->namens) {newAttr->namens = estrdup(newAttr->namens);}
							if (newAttr->name) {newAttr->name = estrdup(newAttr->name);}
							if (newAttr->extraAttributes) {
								HashTable *ht = emalloc(sizeof(HashTable));
								zend_hash_init(ht, zend_hash_num_elements(newAttr->extraAttributes), NULL, delete_extra_attribute, 0);
								zend_hash_copy(ht, newAttr->extraAttributes, copy_extra_attribute);
								newAttr->extraAttributes = ht;
							}

							zend_hash_get_current_key(tmp->attributes, &_key, NULL);
							zend_hash_add_ptr(ht, _key, newAttr);

							zend_hash_move_forward(tmp->attributes);
						} else {
							zend_ulong index;

							schema_attributegroup_fixup(ctx, tmp_attr, ht);
							zend_hash_get_current_key(tmp->attributes, NULL, &index);
							zend_hash_index_del(tmp->attributes, index);
						}
					}
				}
			}
		}
		efree(attr->ref);
		attr->ref = NULL;
	}
}