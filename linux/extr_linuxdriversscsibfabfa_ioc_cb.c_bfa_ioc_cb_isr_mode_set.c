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
struct bfa_ioc_s {int dummy; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */

__attribute__((used)) static void
bfa_ioc_cb_isr_mode_set(struct bfa_ioc_s *ioc, bfa_boolean_t msix)
{
}