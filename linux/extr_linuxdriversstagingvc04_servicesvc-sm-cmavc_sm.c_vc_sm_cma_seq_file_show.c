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
struct sm_pde_t {int /*<<< orphan*/  (* show ) (struct seq_file*,void*) ;} ;
struct seq_file {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct seq_file*,void*) ; 

__attribute__((used)) static int vc_sm_cma_seq_file_show(struct seq_file *s, void *v)
{
	struct sm_pde_t *sm_pde;

	sm_pde = (struct sm_pde_t *)(s->private);

	if (sm_pde && sm_pde->show)
		sm_pde->show(s, v);

	return 0;
}