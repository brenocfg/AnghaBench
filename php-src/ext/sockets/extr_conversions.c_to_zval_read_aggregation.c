#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_8__ {int /*<<< orphan*/  has_error; } ;
struct TYPE_9__ {int /*<<< orphan*/  keys; TYPE_1__ err; } ;
typedef  TYPE_2__ res_context ;
struct TYPE_10__ {int field_offset; int /*<<< orphan*/  (* to_zval ) (char const*,int /*<<< orphan*/ *,TYPE_2__*) ;int /*<<< orphan*/ * name; scalar_t__ name_size; } ;
typedef  TYPE_3__ field_descriptor ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_to_zval_err (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_llist_add_element (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zend_llist_remove_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_symtable_str_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void to_zval_read_aggregation(const char *structure,
									 zval *zarr, /* initialized array */
									 const field_descriptor *descriptors,
									 res_context *ctx)
{
	const field_descriptor	*descr;

	assert(Z_TYPE_P(zarr) == IS_ARRAY);
	assert(Z_ARRVAL_P(zarr) != NULL);

	for (descr = descriptors; descr->name != NULL && !ctx->err.has_error; descr++) {
		zval *new_zv, tmp;

		if (descr->to_zval == NULL) {
			do_to_zval_err(ctx, "No information on how to convert native "
					"field into value for key '%s'", descr->name);
			break;
		}

		ZVAL_NULL(&tmp);
		new_zv = zend_symtable_str_update(Z_ARRVAL_P(zarr), descr->name, descr->name_size - 1, &tmp);

		zend_llist_add_element(&ctx->keys, (void*)&descr->name);
		descr->to_zval(structure + descr->field_offset, new_zv, ctx);
		zend_llist_remove_tail(&ctx->keys);
	}
}