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
struct rds_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rds_mr*) ; 
 int /*<<< orphan*/  rds_destroy_mr (struct rds_mr*) ; 

void __rds_put_mr_final(struct rds_mr *mr)
{
	rds_destroy_mr(mr);
	kfree(mr);
}