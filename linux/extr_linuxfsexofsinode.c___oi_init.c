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
struct exofs_i_info {scalar_t__ i_flags; int /*<<< orphan*/  i_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __oi_init(struct exofs_i_info *oi)
{
	init_waitqueue_head(&oi->i_wq);
	oi->i_flags = 0;
}