#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct rsi {TYPE_4__ out_token; TYPE_3__ out_handle; TYPE_2__ in_token; TYPE_1__ in_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsi_free(struct rsi *rsii)
{
	kfree(rsii->in_handle.data);
	kfree(rsii->in_token.data);
	kfree(rsii->out_handle.data);
	kfree(rsii->out_token.data);
}