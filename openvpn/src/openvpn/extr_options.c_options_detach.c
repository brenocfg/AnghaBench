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
struct options {int /*<<< orphan*/ * client_nat; int /*<<< orphan*/ * routes; int /*<<< orphan*/  gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  clone_push_list (struct options*) ; 
 int /*<<< orphan*/  gc_detach (int /*<<< orphan*/ *) ; 

void
options_detach(struct options *o)
{
    gc_detach(&o->gc);
    o->routes = NULL;
    o->client_nat = NULL;
#if P2MP_SERVER
    clone_push_list(o);
#endif
}