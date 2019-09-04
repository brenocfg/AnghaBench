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
typedef  scalar_t__ u32 ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CAKE_MAX_TINS ; 
 int /*<<< orphan*/  cake_clear_tin (struct Qdisc*,scalar_t__) ; 

__attribute__((used)) static void cake_reset(struct Qdisc *sch)
{
	u32 c;

	for (c = 0; c < CAKE_MAX_TINS; c++)
		cake_clear_tin(sch, c);
}