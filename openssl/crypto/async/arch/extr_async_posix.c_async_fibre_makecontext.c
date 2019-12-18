#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ss_sp; int /*<<< orphan*/  ss_size; } ;
struct TYPE_8__ {TYPE_1__ uc_stack; int /*<<< orphan*/ * uc_link; } ;
struct TYPE_7__ {TYPE_3__ fibre; scalar_t__ env_init; } ;
typedef  TYPE_2__ async_fibre ;

/* Variables and functions */
 int /*<<< orphan*/ * OPENSSL_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STACKSIZE ; 
 int /*<<< orphan*/  async_start_func ; 
 scalar_t__ getcontext (TYPE_3__*) ; 
 int /*<<< orphan*/  makecontext (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int async_fibre_makecontext(async_fibre *fibre)
{
    fibre->env_init = 0;
    if (getcontext(&fibre->fibre) == 0) {
        fibre->fibre.uc_stack.ss_sp = OPENSSL_malloc(STACKSIZE);
        if (fibre->fibre.uc_stack.ss_sp != NULL) {
            fibre->fibre.uc_stack.ss_size = STACKSIZE;
            fibre->fibre.uc_link = NULL;
            makecontext(&fibre->fibre, async_start_func, 0);
            return 1;
        }
    } else {
        fibre->fibre.uc_stack.ss_sp = NULL;
    }
    return 0;
}