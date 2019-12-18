#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_1__* sdlTypePtr ;
struct TYPE_5__ {struct TYPE_5__* restrictions; struct TYPE_5__* enumeration; int /*<<< orphan*/  pattern; int /*<<< orphan*/  whiteSpace; int /*<<< orphan*/  maxLength; int /*<<< orphan*/  minLength; int /*<<< orphan*/  length; int /*<<< orphan*/  fractionDigits; int /*<<< orphan*/  totalDigits; int /*<<< orphan*/  maxInclusive; int /*<<< orphan*/  maxExclusive; int /*<<< orphan*/  minInclusive; int /*<<< orphan*/  minExclusive; scalar_t__ model; struct TYPE_5__* attributes; struct TYPE_5__* elements; struct TYPE_5__* fixed; struct TYPE_5__* def; struct TYPE_5__* namens; struct TYPE_5__* name; } ;

/* Variables and functions */
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_model_persistent_int (scalar_t__) ; 
 int /*<<< orphan*/  delete_restriction_var_char_persistent_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_restriction_var_int_persistent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (TYPE_1__*) ; 

void delete_type_persistent(zval *zv)
{
	sdlTypePtr type = Z_PTR_P(zv);
	if (type->name) {
		free(type->name);
	}
	if (type->namens) {
		free(type->namens);
	}
	if (type->def) {
		free(type->def);
	}
	if (type->fixed) {
		free(type->fixed);
	}
	if (type->elements) {
		zend_hash_destroy(type->elements);
		free(type->elements);
	}
	if (type->attributes) {
		zend_hash_destroy(type->attributes);
		free(type->attributes);
	}
	if (type->model) {
		delete_model_persistent_int(type->model);
	}
	if (type->restrictions) {
		delete_restriction_var_int_persistent(type->restrictions->minExclusive);
		delete_restriction_var_int_persistent(type->restrictions->minInclusive);
		delete_restriction_var_int_persistent(type->restrictions->maxExclusive);
		delete_restriction_var_int_persistent(type->restrictions->maxInclusive);
		delete_restriction_var_int_persistent(type->restrictions->totalDigits);
		delete_restriction_var_int_persistent(type->restrictions->fractionDigits);
		delete_restriction_var_int_persistent(type->restrictions->length);
		delete_restriction_var_int_persistent(type->restrictions->minLength);
		delete_restriction_var_int_persistent(type->restrictions->maxLength);
		delete_restriction_var_char_persistent_int(type->restrictions->whiteSpace);
		delete_restriction_var_char_persistent_int(type->restrictions->pattern);
		if (type->restrictions->enumeration) {
			zend_hash_destroy(type->restrictions->enumeration);
			free(type->restrictions->enumeration);
		}
		free(type->restrictions);
	}
	free(type);
}