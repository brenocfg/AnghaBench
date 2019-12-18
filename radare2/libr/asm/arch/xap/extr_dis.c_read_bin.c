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
struct state {int /*<<< orphan*/  s_off; int /*<<< orphan*/  s_buf; } ;
struct directive {scalar_t__ d_off; int /*<<< orphan*/  d_inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_bin(struct state *s, struct directive *d) {
	memcpy(&d->d_inst, s->s_buf, sizeof(d->d_inst));
	d->d_off = s->s_off++;
	return 1;
}