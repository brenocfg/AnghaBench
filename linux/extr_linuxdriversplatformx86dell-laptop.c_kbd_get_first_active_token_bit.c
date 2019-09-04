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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int kbd_get_token_bit (int) ; 
 int /*<<< orphan*/  kbd_tokens ; 

__attribute__((used)) static int kbd_get_first_active_token_bit(void)
{
	int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(kbd_tokens); ++i) {
		ret = kbd_get_token_bit(i);
		if (ret == 1)
			return i;
	}

	return ret;
}