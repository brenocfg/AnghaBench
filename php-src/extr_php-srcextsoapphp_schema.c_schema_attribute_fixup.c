#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * attributes; } ;
typedef  TYPE_1__ sdlCtx ;
typedef  TYPE_2__* sdlAttributePtr ;
struct TYPE_6__ {char* ref; char* name; char* namens; char* def; char* fixed; int /*<<< orphan*/  encode; int /*<<< orphan*/ * extraAttributes; int /*<<< orphan*/  use; int /*<<< orphan*/  form; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  XSD_FORM_DEFAULT ; 
 int /*<<< orphan*/  XSD_USE_DEFAULT ; 
 int /*<<< orphan*/  copy_extra_attribute ; 
 int /*<<< orphan*/  delete_extra_attribute ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/ * emalloc (int) ; 
 void* estrdup (char*) ; 
 scalar_t__ schema_find_by_ref (int /*<<< orphan*/ *,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  zend_hash_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_num_elements (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void schema_attribute_fixup(sdlCtx *ctx, sdlAttributePtr attr)
{
	sdlAttributePtr tmp;

	if (attr->ref != NULL) {
		if (ctx->attributes != NULL) {
			tmp = (sdlAttributePtr)schema_find_by_ref(ctx->attributes, attr->ref);
			if (tmp) {
				schema_attribute_fixup(ctx, tmp);
				if (tmp->name != NULL && attr->name == NULL) {
					attr->name = estrdup(tmp->name);
				}
				if (tmp->namens != NULL && attr->namens == NULL) {
					attr->namens = estrdup(tmp->namens);
				}
				if (tmp->def != NULL && attr->def == NULL) {
					attr->def = estrdup(tmp->def);
				}
				if (tmp->fixed != NULL && attr->fixed == NULL) {
					attr->fixed = estrdup(tmp->fixed);
				}
				if (attr->form == XSD_FORM_DEFAULT) {
					attr->form = tmp->form;
				}
				if (attr->use == XSD_USE_DEFAULT) {
					attr->use  = tmp->use;
				}
				if (tmp->extraAttributes != NULL) {
					attr->extraAttributes = emalloc(sizeof(HashTable));
					zend_hash_init(attr->extraAttributes, zend_hash_num_elements(tmp->extraAttributes), NULL, delete_extra_attribute, 0);
					zend_hash_copy(attr->extraAttributes, tmp->extraAttributes, copy_extra_attribute);
				}
				attr->encode = tmp->encode;
			}
		}
		if (attr->name == NULL && attr->ref != NULL) {
			char *name = strrchr(attr->ref, ':');
			if (name) {
				attr->name = estrdup(name+1);
			} else{
				attr->name = estrdup(attr->ref);
			}
		}
		efree(attr->ref);
		attr->ref = NULL;
	}
}