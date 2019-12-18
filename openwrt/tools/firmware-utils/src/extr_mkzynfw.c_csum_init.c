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
struct csum_state {scalar_t__ tmp; scalar_t__ sum; scalar_t__ odd; } ;

/* Variables and functions */

void
csum_init(struct csum_state *css)
{
	css->odd = 0;
	css->sum = 0;
	css->tmp = 0;
}