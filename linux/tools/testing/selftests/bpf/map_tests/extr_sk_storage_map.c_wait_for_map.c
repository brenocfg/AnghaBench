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
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_stopped () ; 
 int /*<<< orphan*/  sk_storage_map ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static bool wait_for_map(void)
{
	while (READ_ONCE(sk_storage_map) == -1 && !is_stopped())
		usleep(50);

	return !is_stopped();
}