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
 int /*<<< orphan*/  bpf_user_rnd_state ; 
 int /*<<< orphan*/  prandom_init_once (int /*<<< orphan*/ *) ; 

void bpf_user_rnd_init_once(void)
{
	prandom_init_once(&bpf_user_rnd_state);
}