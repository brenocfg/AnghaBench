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
struct TYPE_3__ {int (* async_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  async_cb_arg; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_async_wait_ctx_cb(void *arg)
{
    SSL *s = (SSL *)arg;

    return s->async_cb(s, s->async_cb_arg);
}