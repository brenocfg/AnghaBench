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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct acpiphp_context {TYPE_1__ func; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_bridge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpiphp_let_context_go(struct acpiphp_context *context)
{
	put_bridge(context->func.parent);
}