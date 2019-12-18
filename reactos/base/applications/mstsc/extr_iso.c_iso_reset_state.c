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
 int /*<<< orphan*/  g_encryption ; 
 int /*<<< orphan*/  g_encryption_initial ; 
 int /*<<< orphan*/  tcp_reset_state () ; 

void
iso_reset_state(void)
{
	g_encryption = g_encryption_initial;
	tcp_reset_state();
}