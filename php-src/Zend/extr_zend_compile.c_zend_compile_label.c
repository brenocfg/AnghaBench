#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_6__ {int /*<<< orphan*/  opline_num; int /*<<< orphan*/  brk_cont; } ;
typedef  TYPE_1__ zend_label ;
struct TYPE_7__ {int /*<<< orphan*/ * child; } ;
typedef  TYPE_2__ zend_ast ;
struct TYPE_8__ {int /*<<< orphan*/  labels; int /*<<< orphan*/  current_brk_cont; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (int /*<<< orphan*/ ) ; 
 TYPE_5__ CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  get_next_op_number () ; 
 int /*<<< orphan*/  label_ptr_dtor ; 
 int /*<<< orphan*/ * zend_ast_get_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_add_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zend_compile_label(zend_ast *ast) /* {{{ */
{
	zend_string *label = zend_ast_get_str(ast->child[0]);
	zend_label dest;

	if (!CG(context).labels) {
		ALLOC_HASHTABLE(CG(context).labels);
		zend_hash_init(CG(context).labels, 8, NULL, label_ptr_dtor, 0);
	}

	dest.brk_cont = CG(context).current_brk_cont;
	dest.opline_num = get_next_op_number();

	if (!zend_hash_add_mem(CG(context).labels, label, &dest, sizeof(zend_label))) {
		zend_error_noreturn(E_COMPILE_ERROR, "Label '%s' already defined", ZSTR_VAL(label));
	}
}