#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct symbol {int dummy; } ;
struct call_path {int in_kernel; int /*<<< orphan*/  children; int /*<<< orphan*/  rb_node; scalar_t__ db_id; int /*<<< orphan*/  ip; struct symbol* sym; struct call_path* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 

__attribute__((used)) static void call_path__init(struct call_path *cp, struct call_path *parent,
			    struct symbol *sym, u64 ip, bool in_kernel)
{
	cp->parent = parent;
	cp->sym = sym;
	cp->ip = sym ? 0 : ip;
	cp->db_id = 0;
	cp->in_kernel = in_kernel;
	RB_CLEAR_NODE(&cp->rb_node);
	cp->children = RB_ROOT;
}