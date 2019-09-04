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
struct state {int s_prefix; int s_prefix_val; } ;
struct directive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_fixed (struct state*,struct directive*) ; 
 int /*<<< orphan*/  decode_known (struct state*,struct directive*) ; 
 int /*<<< orphan*/  decode_unknown (struct state*,struct directive*) ; 

__attribute__((used)) static void xap_decode(struct state *s, struct directive *d) {
	int prefix = s->s_prefix;
	if (!decode_fixed (s, d))
		if (!decode_known (s, d))
			decode_unknown (s, d);
	if (s->s_prefix == prefix)
		s->s_prefix_val = s->s_prefix = 0;
}