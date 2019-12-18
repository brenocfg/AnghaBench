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
struct TYPE_4__ {struct TYPE_4__* parent; struct TYPE_4__** child; } ;
typedef  TYPE_1__ zend_sym_node ;

/* Variables and functions */
 TYPE_1__* symbols ; 

__attribute__((used)) static void zend_syms_rotateleft(zend_sym_node *p) {
	zend_sym_node *r = p->child[1];
	p->child[1] = r->child[0];
	if (r->child[0]) {
		r->child[0]->parent = p;
	}
	r->parent = p->parent;
	if (p->parent == NULL) {
		symbols = r;
	} else if (p->parent->child[0] == p) {
		p->parent->child[0] = r;
	} else {
		p->parent->child[1] = r;
	}
	r->child[0] = p;
	p->parent = r;
}