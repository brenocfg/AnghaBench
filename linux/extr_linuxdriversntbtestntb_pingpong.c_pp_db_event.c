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
struct pp_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pp_pong (struct pp_ctx*) ; 

__attribute__((used)) static void pp_db_event(void *ctx, int vec)
{
	struct pp_ctx *pp = ctx;

	pp_pong(pp);
}