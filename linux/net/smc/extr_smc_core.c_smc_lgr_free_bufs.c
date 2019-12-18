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
struct smc_link_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __smc_lgr_free_bufs (struct smc_link_group*,int) ; 

__attribute__((used)) static void smc_lgr_free_bufs(struct smc_link_group *lgr)
{
	/* free send buffers */
	__smc_lgr_free_bufs(lgr, false);
	/* free rmbs */
	__smc_lgr_free_bufs(lgr, true);
}