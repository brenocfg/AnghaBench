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
 int /*<<< orphan*/ ** dummy_page ; 
 scalar_t__ fake_buffer ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void free_fake_buffer(void)
{
	if (fake_buffer) {
		int i;
		for (i = 0; i < 2; i++)
			if (dummy_page[i]) {
				free_page((unsigned long)dummy_page[i]);
				dummy_page[i] = NULL;
			}
	}
}