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
struct module {int /*<<< orphan*/  taints; } ;
typedef  enum lockdep_ok { ____Placeholder_lockdep_ok } lockdep_ok ;

/* Variables and functions */
 int /*<<< orphan*/  add_taint (unsigned int,int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void add_taint_module(struct module *mod, unsigned flag,
				    enum lockdep_ok lockdep_ok)
{
	add_taint(flag, lockdep_ok);
	set_bit(flag, &mod->taints);
}