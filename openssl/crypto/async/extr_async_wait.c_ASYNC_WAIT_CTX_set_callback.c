#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* callback_arg; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  ASYNC_callback_fn ;
typedef  TYPE_1__ ASYNC_WAIT_CTX ;

/* Variables and functions */

int ASYNC_WAIT_CTX_set_callback(ASYNC_WAIT_CTX *ctx,
                                ASYNC_callback_fn callback,
                                void *callback_arg)
{
      if (ctx == NULL)
          return 0;

      ctx->callback = callback;
      ctx->callback_arg = callback_arg;
      return 1;
}