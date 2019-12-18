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
 int /*<<< orphan*/  ZVAL_PTR (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_restriction_var_char_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_restriction_var_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (TYPE_1__*) ; 

void delete_type(zval *zv)
{
	sdlTypePtr type = Z_PTR_P(zv);

	if (type->name) {
		efree(type->name);
	}
	if (type->namens) {
		efree(type->namens);
	}
	if (type->def) {
		efree(type->def);
	}
	if (type->fixed) {
		efree(type->fixed);
	}
	if (type->elements) {
		zend_hash_destroy(type->elements);
		efree(type->elements);
	}
	if (type->attributes) {
		zend_hash_destroy(type->attributes);
		efree(type->attributes);
	}
	if (type->model) {
		zval zv;
		ZVAL_PTR(&zv, type->model);
		delete_model(&zv);
	}
	if (type->restrictions) {
		delete_restriction_var_int(type->restrictions->minExclusive);
		delete_restriction_var_int(type->restrictions->minInclusive);
		delete_restriction_var_int(type->restrictions->maxExclusive);
		delete_restriction_var_int(type->restrictions->maxInclusive);
		delete_restriction_var_int(type->restrictions->totalDigits);
		delete_restriction_var_int(type->restrictions->fractionDigits);
		delete_restriction_var_int(type->restrictions->length);
		delete_restriction_var_int(type->restrictions->minLength);
		delete_restriction_var_int(type->restrictions->maxLength);
		delete_restriction_var_char_int(type->restrictions->whiteSpace);
		delete_restriction_var_char_int(type->restrictions->pattern);
		if (type->restrictions->enumeration) {
			zend_hash_destroy(type->restrictions->enumeration);
			efree(type->restrictions->enumeration);
		}
		efree(type->restrictions);
	}
	efree(type);
}