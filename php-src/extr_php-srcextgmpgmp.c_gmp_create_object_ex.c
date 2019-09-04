#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * handlers; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  int /*<<< orphan*/  mpz_ptr ;
struct TYPE_8__ {TYPE_1__ std; int /*<<< orphan*/  num; } ;
typedef  TYPE_2__ gmp_object ;

/* Variables and functions */
 TYPE_2__* emalloc (scalar_t__) ; 
 int /*<<< orphan*/  gmp_object_handlers ; 
 int /*<<< orphan*/  mpz_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_properties_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_object_properties_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline zend_object *gmp_create_object_ex(zend_class_entry *ce, mpz_ptr *gmpnum_target) /* {{{ */
{
	gmp_object *intern = emalloc(sizeof(gmp_object) + zend_object_properties_size(ce));

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);

	mpz_init(intern->num);
	*gmpnum_target = intern->num;
	intern->std.handlers = &gmp_object_handlers;

	return &intern->std;
}