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

/* Variables and functions */
 int nf_ct_extend_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_seqadj_extend ; 

int nf_conntrack_seqadj_init(void)
{
	return nf_ct_extend_register(&nf_ct_seqadj_extend);
}