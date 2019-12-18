#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_17__ {int /*<<< orphan*/  ce; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  UTransliterator ;
struct TYPE_18__ {int /*<<< orphan*/ * utrans; int /*<<< orphan*/  zo; } ;
typedef  TYPE_2__ Transliterator_object ;
struct TYPE_16__ {TYPE_1__* (* create_object ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  INTL_DATA_ERROR_CODE (TYPE_2__*) ; 
 int /*<<< orphan*/ * INTL_DATA_ERROR_P (TYPE_2__*) ; 
 int /*<<< orphan*/  TRANSLITERATOR_ERROR_CODE (TYPE_2__*) ; 
 int /*<<< orphan*/  TRANSLITERATOR_ERROR_CODE_P (TYPE_2__*) ; 
 int /*<<< orphan*/  TRANSLITERATOR_ERROR_P (TYPE_2__*) ; 
 TYPE_10__* Transliterator_ce_ptr ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * intl_error_get_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intl_error_set_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_errors_set_custom_msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* php_intl_transliterator_fetch_object (TYPE_1__*) ; 
 TYPE_1__* stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transliterator_object_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transliterator_object_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/ * utrans_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_objects_clone_members (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_object *Transliterator_clone_obj( zend_object *object )
{
	Transliterator_object *to_orig,
	                      *to_new;
	zend_object 		  *ret_val;
	intl_error_reset( NULL );

	to_orig = php_intl_transliterator_fetch_object( object );
	intl_error_reset( INTL_DATA_ERROR_P( to_orig ) );
	ret_val = Transliterator_ce_ptr->create_object( object->ce );
	to_new  = php_intl_transliterator_fetch_object( ret_val );

	zend_objects_clone_members( &to_new->zo, &to_orig->zo );

	if( to_orig->utrans != NULL )
	{
		zval			tempz; /* dummy zval to pass to transliterator_object_construct */

		/* guaranteed to return NULL if it fails */
		UTransliterator *utrans = utrans_clone( to_orig->utrans, TRANSLITERATOR_ERROR_CODE_P( to_orig ) );

		if( U_FAILURE( TRANSLITERATOR_ERROR_CODE( to_orig ) ) )
			goto err;

		ZVAL_OBJ(&tempz, ret_val);
		transliterator_object_construct( &tempz, utrans,
			TRANSLITERATOR_ERROR_CODE_P( to_orig ) );

		if( U_FAILURE( TRANSLITERATOR_ERROR_CODE( to_orig ) ) )
		{
			zend_string *err_msg;
err:

			if( utrans != NULL )
				transliterator_object_destroy( to_new );

			/* set the error anyway, in case in the future we decide not to
			 * throw an error. It also helps build the error message */
			intl_error_set_code( NULL, INTL_DATA_ERROR_CODE( to_orig ) );
			intl_errors_set_custom_msg( TRANSLITERATOR_ERROR_P( to_orig ),
				"Could not clone transliterator", 0 );

			err_msg = intl_error_get_message( TRANSLITERATOR_ERROR_P( to_orig ) );
			zend_throw_error( NULL, "%s", ZSTR_VAL(err_msg) );
			zend_string_free( err_msg ); /* if it's changed into a warning */
			/* do not destroy tempz; we need to return something */
		}
	}
	else
	{
		/* We shouldn't have unconstructed objects in the first place */
		php_error_docref( NULL, E_WARNING,
			"Cloning unconstructed transliterator." );
	}

	return ret_val;
}