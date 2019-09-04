#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* list_next; int /*<<< orphan*/  val_len; int /*<<< orphan*/ * val; int /*<<< orphan*/  var_len; int /*<<< orphan*/  var; } ;
typedef  TYPE_1__ fcgi_hash_bucket ;
struct TYPE_5__ {TYPE_1__* list; } ;
typedef  TYPE_2__ fcgi_hash ;
typedef  int /*<<< orphan*/  (* fcgi_apply_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 scalar_t__ EXPECTED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcgi_hash_apply(fcgi_hash *h, fcgi_apply_func func, void *arg)
{
	fcgi_hash_bucket *p	= h->list;

	while (p) {
		if (EXPECTED(p->val != NULL)) {
			func(p->var, p->var_len, p->val, p->val_len, arg);
		}
		p = p->list_next;
	}
}