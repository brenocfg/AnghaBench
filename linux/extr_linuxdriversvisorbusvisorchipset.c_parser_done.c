#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parser_context {scalar_t__ param_bytes; } ;
struct TYPE_2__ {int /*<<< orphan*/  controlvm_payload_bytes_buffered; } ;

/* Variables and functions */
 TYPE_1__* chipset_dev ; 
 int /*<<< orphan*/  kfree (struct parser_context*) ; 

__attribute__((used)) static void parser_done(struct parser_context *ctx)
{
	chipset_dev->controlvm_payload_bytes_buffered -= ctx->param_bytes;
	kfree(ctx);
}