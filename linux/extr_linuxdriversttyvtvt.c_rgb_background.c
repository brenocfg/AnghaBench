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
struct vc_data {int vc_color; } ;
struct rgb {int r; int g; int b; } ;

/* Variables and functions */

__attribute__((used)) static void rgb_background(struct vc_data *vc, const struct rgb *c)
{
	/* For backgrounds, err on the dark side. */
	vc->vc_color = (vc->vc_color & 0x0f)
		| (c->r&0x80) >> 1 | (c->g&0x80) >> 2 | (c->b&0x80) >> 3;
}