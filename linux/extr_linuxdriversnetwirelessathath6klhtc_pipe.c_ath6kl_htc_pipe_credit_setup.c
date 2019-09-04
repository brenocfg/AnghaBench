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
struct htc_target {int dummy; } ;
struct ath6kl_htc_credit_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ath6kl_htc_pipe_credit_setup(struct htc_target *target,
					struct ath6kl_htc_credit_info *info)
{
	return 0;
}