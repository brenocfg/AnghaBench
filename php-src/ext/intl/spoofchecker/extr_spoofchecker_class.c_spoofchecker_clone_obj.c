#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ce; } ;
typedef  TYPE_1__ zend_object ;
struct TYPE_14__ {TYPE_1__* (* create_object ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  zo; int /*<<< orphan*/  uspoof; } ;
typedef  TYPE_2__ Spoofchecker_object ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  SPOOFCHECKER_ERROR_CODE (TYPE_2__*) ; 
 int /*<<< orphan*/  SPOOFCHECKER_ERROR_CODE_P (TYPE_2__*) ; 
 int /*<<< orphan*/  SPOOFCHECKER_ERROR_P (TYPE_2__*) ; 
 TYPE_8__* Spoofchecker_ce_ptr ; 
 int /*<<< orphan*/  Spoofchecker_objects_free (int /*<<< orphan*/ *) ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* php_intl_spoofchecker_fetch_object (TYPE_1__*) ; 
 TYPE_1__* stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uspoof_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_objects_clone_members (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_object *spoofchecker_clone_obj(zend_object *object) /* {{{ */
{
	zend_object *new_obj_val;
	Spoofchecker_object *sfo, *new_sfo;

    sfo = php_intl_spoofchecker_fetch_object(object);
    intl_error_reset(SPOOFCHECKER_ERROR_P(sfo));

	new_obj_val = Spoofchecker_ce_ptr->create_object(object->ce);
	new_sfo = php_intl_spoofchecker_fetch_object(new_obj_val);
	/* clone standard parts */
	zend_objects_clone_members(&new_sfo->zo, &sfo->zo);
	/* clone internal object */
	new_sfo->uspoof = uspoof_clone(sfo->uspoof, SPOOFCHECKER_ERROR_CODE_P(new_sfo));
	if(U_FAILURE(SPOOFCHECKER_ERROR_CODE(new_sfo))) {
		/* set up error in case error handler is interested */
		intl_error_set( NULL, SPOOFCHECKER_ERROR_CODE(new_sfo), "Failed to clone SpoofChecker object", 0 );
		Spoofchecker_objects_free(&new_sfo->zo); /* free new object */
		zend_error(E_ERROR, "Failed to clone SpoofChecker object");
	}
	return new_obj_val;
}