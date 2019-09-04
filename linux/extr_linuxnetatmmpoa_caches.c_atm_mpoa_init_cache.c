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
struct mpoa_client {int /*<<< orphan*/ * eg_ops; int /*<<< orphan*/ * in_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  egress_ops ; 
 int /*<<< orphan*/  ingress_ops ; 

void atm_mpoa_init_cache(struct mpoa_client *mpc)
{
	mpc->in_ops = &ingress_ops;
	mpc->eg_ops = &egress_ops;
}