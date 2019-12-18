#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* fn ) (TYPE_1__ const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ OBJ_NAME ;
typedef  TYPE_2__ OBJ_DOALL ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_all_fn(const OBJ_NAME *name, OBJ_DOALL *d)
{
    if (name->type == d->type)
        d->fn(name, d->arg);
}