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
struct ef4_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_CHANNEL_MAGIC_TEST (struct ef4_channel*) ; 
 int /*<<< orphan*/  ef4_farch_magic_event (struct ef4_channel*,int /*<<< orphan*/ ) ; 

void ef4_farch_ev_test_generate(struct ef4_channel *channel)
{
	ef4_farch_magic_event(channel, EF4_CHANNEL_MAGIC_TEST(channel));
}