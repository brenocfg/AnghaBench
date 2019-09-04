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
typedef  int /*<<< orphan*/  u8 ;
struct ts_state {scalar_t__ cb; } ;
struct ts_linear_state {unsigned int len; int /*<<< orphan*/ * data; } ;
struct ts_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

__attribute__((used)) static unsigned int get_linear_data(unsigned int consumed, const u8 **dst,
				    struct ts_config *conf,
				    struct ts_state *state)
{
	struct ts_linear_state *st = (struct ts_linear_state *) state->cb;

	if (likely(consumed < st->len)) {
		*dst = st->data + consumed;
		return st->len - consumed;
	}

	return 0;
}