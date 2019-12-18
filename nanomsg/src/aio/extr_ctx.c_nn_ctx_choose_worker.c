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
struct nn_worker {int dummy; } ;
struct nn_ctx {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 struct nn_worker* nn_pool_choose_worker (int /*<<< orphan*/ ) ; 

struct nn_worker *nn_ctx_choose_worker (struct nn_ctx *self)
{
    return nn_pool_choose_worker (self->pool);
}