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
struct pagevec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pagevec_lru_add_fn ; 
 int /*<<< orphan*/  pagevec_lru_move_fn (struct pagevec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __pagevec_lru_add(struct pagevec *pvec)
{
	pagevec_lru_move_fn(pvec, __pagevec_lru_add_fn, NULL);
}