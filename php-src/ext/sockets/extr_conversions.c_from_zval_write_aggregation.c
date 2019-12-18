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
typedef  TYPE_2__ ser_context ;
struct TYPE_10__ {char* name; int field_offset; scalar_t__ required; int /*<<< orphan*/  (* from_zval ) (int /*<<< orphan*/ *,char*,TYPE_2__*) ;scalar_t__ name_size; } ;
typedef  TYPE_3__ field_descriptor ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/  const*) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  do_from_zval_err (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  zend_llist_add_element (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zend_llist_remove_tail (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void from_zval_write_aggregation(const zval *container,
										char *structure,
										const field_descriptor *descriptors,
										ser_context *ctx)
{
	const field_descriptor	*descr;
	zval					*elem;

	if (Z_TYPE_P(container) != IS_ARRAY) {
		do_from_zval_err(ctx, "%s", "expected an array here");
	}

	for (descr = descriptors; descr->name != NULL && !ctx->err.has_error; descr++) {
		if ((elem = zend_hash_str_find(Z_ARRVAL_P(container),
				descr->name, descr->name_size - 1)) != NULL) {

			if (descr->from_zval == NULL) {
				do_from_zval_err(ctx, "No information on how to convert value "
						"of key '%s'", descr->name);
				break;
			}

			zend_llist_add_element(&ctx->keys, (void*)&descr->name);
			descr->from_zval(elem, ((char*)structure) + descr->field_offset, ctx);
			zend_llist_remove_tail(&ctx->keys);

		} else if (descr->required) {
			do_from_zval_err(ctx, "The key '%s' is required", descr->name);
			break;
		}
	}
}