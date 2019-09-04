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
struct qbman_swp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QBMAN_CENA_SWP_CR ; 
 void* qbman_get_cmd (struct qbman_swp*,int /*<<< orphan*/ ) ; 

void *qbman_swp_mc_start(struct qbman_swp *p)
{
	return qbman_get_cmd(p, QBMAN_CENA_SWP_CR);
}