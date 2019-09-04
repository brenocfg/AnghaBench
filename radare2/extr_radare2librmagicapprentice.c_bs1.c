#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* ut32 ;
struct TYPE_2__ {void* q; } ;
struct r_magic {void* num_mask; TYPE_1__ value; void* str_flags; void* str_range; int /*<<< orphan*/  type; void* lineno; void* in_offset; void* offset; int /*<<< orphan*/  cont_level; } ;

/* Variables and functions */
 scalar_t__ MAGIC_IS_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap2 (int /*<<< orphan*/ ) ; 
 void* swap4 (void*) ; 
 void* swap8 (void*) ; 

__attribute__((used)) static void bs1(struct r_magic *m) {
	m->cont_level = swap2(m->cont_level);
	m->offset = swap4((ut32)m->offset);
	m->in_offset = swap4((ut32)m->in_offset);
	m->lineno = swap4((ut32)m->lineno);
	if (MAGIC_IS_STRING (m->type)) {
		m->str_range = swap4(m->str_range);
		m->str_flags = swap4(m->str_flags);
	} else {
		m->value.q = swap8(m->value.q);
		m->num_mask = swap8(m->num_mask);
	}
}