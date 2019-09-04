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
struct regs_dump {scalar_t__ regs; } ;
struct perf_sample {struct regs_dump user_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  regs__printf (char*,struct regs_dump*) ; 

__attribute__((used)) static void regs_user__printf(struct perf_sample *sample)
{
	struct regs_dump *user_regs = &sample->user_regs;

	if (user_regs->regs)
		regs__printf("user", user_regs);
}