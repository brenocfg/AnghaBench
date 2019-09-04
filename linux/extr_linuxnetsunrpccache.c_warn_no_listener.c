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
struct cache_detail {scalar_t__ last_warn; scalar_t__ last_close; int /*<<< orphan*/  (* warn_no_listener ) (struct cache_detail*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct cache_detail*,int) ; 

__attribute__((used)) static void warn_no_listener(struct cache_detail *detail)
{
	if (detail->last_warn != detail->last_close) {
		detail->last_warn = detail->last_close;
		if (detail->warn_no_listener)
			detail->warn_no_listener(detail, detail->last_close != 0);
	}
}