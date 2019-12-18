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
struct kioctx {int dummy; } ;

/* Variables and functions */
 int __get_reqs_available (struct kioctx*) ; 
 int /*<<< orphan*/  user_refill_reqs_available (struct kioctx*) ; 

__attribute__((used)) static bool get_reqs_available(struct kioctx *ctx)
{
	if (__get_reqs_available(ctx))
		return true;
	user_refill_reqs_available(ctx);
	return __get_reqs_available(ctx);
}