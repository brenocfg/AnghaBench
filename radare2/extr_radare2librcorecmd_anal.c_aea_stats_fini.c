#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  inputregs; int /*<<< orphan*/  regwrite; int /*<<< orphan*/  regread; int /*<<< orphan*/  regs; } ;
typedef  TYPE_1__ AeaStats ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aea_stats_fini (AeaStats *stats) {
	R_FREE (stats->regs);
	R_FREE (stats->regread);
	R_FREE (stats->regwrite);
	R_FREE (stats->inputregs);
}