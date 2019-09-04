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
struct ti_abb {int /*<<< orphan*/  int_base; int /*<<< orphan*/  txdone_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ti_abb_clear_txdone(const struct ti_abb *abb)
{
	writel(abb->txdone_mask, abb->int_base);
}