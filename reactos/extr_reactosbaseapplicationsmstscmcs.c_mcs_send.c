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
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  MCS_GLOBAL_CHANNEL ; 
 int /*<<< orphan*/  mcs_send_to_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mcs_send(STREAM s)
{
	mcs_send_to_channel(s, MCS_GLOBAL_CHANNEL);
}