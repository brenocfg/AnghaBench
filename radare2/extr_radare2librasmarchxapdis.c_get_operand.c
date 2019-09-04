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
struct state {int s_prefix; int /*<<< orphan*/  s_prefix_val; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_operand; } ;
struct directive {TYPE_1__ d_inst; } ;

/* Variables and functions */
 int get_num (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_operand(struct state *s, struct directive *d) {
	int total = get_num(d->d_inst.in_operand, 0);
	if (s->s_prefix)
		total += get_num(s->s_prefix_val, 8);
	if (s->s_prefix == 2)
		total += get_num(s->s_prefix_val, 16);
	return total;
}