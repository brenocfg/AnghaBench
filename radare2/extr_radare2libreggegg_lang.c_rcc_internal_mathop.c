#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char varxs; int /*<<< orphan*/  varsize; } ;
struct TYPE_13__ {TYPE_1__ lang; TYPE_2__* remit; } ;
struct TYPE_12__ {char const* (* regs ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mathop ) (TYPE_3__*,char,int /*<<< orphan*/ ,char,char*,char*) ;int /*<<< orphan*/  (* load_ptr ) (TYPE_3__*,char*) ;int /*<<< orphan*/  (* load ) (TYPE_3__*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ REggEmit ;
typedef  TYPE_3__ REgg ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 scalar_t__ get_op (char**) ; 
 scalar_t__ is_space (char) ; 
 scalar_t__ is_var (char*) ; 
 char* r_egg_mkvar (TYPE_3__*,char*,char*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 char const* stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,char*) ; 
 char const* stub4 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,char,int /*<<< orphan*/ ,char,char*,char*) ; 

__attribute__((used)) static void rcc_internal_mathop(REgg *egg, const char *ptr, char *ep, char op) {
	char *p, *q, *oldp;	// avoid mem leak
	char type = ' ';
	char buf[64];	// may cause stack overflow
	oldp = p = q = strdup (ptr);
	if (get_op (&q)) {
		*q = '\x00';
	}
	REggEmit *e = egg->remit;
	while (*p && is_space (*p)) {
		p++;
	}
	if (is_var (p)) {
		p = r_egg_mkvar (egg, buf, p, 0);
		if (egg->lang.varxs == '*') {
			e->load (egg, p, egg->lang.varsize);
			R_FREE (oldp);
			oldp = p = strdup (e->regs (egg, 0));
			// XXX: which will go wrong in arm
			// for reg used in emit.load in arm is r7 not r0
		} else if (egg->lang.varxs == '&') {
			e->load_ptr (egg, p);
			R_FREE (oldp);
			oldp = p = strdup (e->regs (egg, 0));
		}
		type = ' ';
	} else {
		type = '$';
	}
	if (*p) {
		e->mathop (egg, op, egg->lang.varsize, type, p, ep);
	}
	if (p != oldp) {
		R_FREE (p);
	}
	R_FREE (oldp);
	R_FREE (ep);
}