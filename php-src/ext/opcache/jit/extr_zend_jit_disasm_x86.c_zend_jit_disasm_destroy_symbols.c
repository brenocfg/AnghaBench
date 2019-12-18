#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__** child; } ;
typedef  TYPE_1__ zend_sym_node ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void zend_jit_disasm_destroy_symbols(zend_sym_node *n) {
	if (n) {
		if (n->child[0]) {
			zend_jit_disasm_destroy_symbols(n->child[0]);
		} else if (n->child[1]) {
			zend_jit_disasm_destroy_symbols(n->child[1]);
		}
		free(n);
	}
}