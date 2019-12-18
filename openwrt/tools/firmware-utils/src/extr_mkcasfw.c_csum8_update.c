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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct csum_state {int /*<<< orphan*/  val; } ;

/* Variables and functions */

void
csum8_update(uint8_t *p, uint32_t len, struct csum_state *css)
{
	for ( ; len > 0; len --) {
		css->val += *p++;
	}
}