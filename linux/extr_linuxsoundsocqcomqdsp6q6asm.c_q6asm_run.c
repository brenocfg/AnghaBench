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
typedef  int /*<<< orphan*/  uint32_t ;
struct audio_client {int dummy; } ;

/* Variables and functions */
 int __q6asm_run (struct audio_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int q6asm_run(struct audio_client *ac, uint32_t flags,
	      uint32_t msw_ts, uint32_t lsw_ts)
{
	return __q6asm_run(ac, flags, msw_ts, lsw_ts, true);
}