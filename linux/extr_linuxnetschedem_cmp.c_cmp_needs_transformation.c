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
struct tcf_em_cmp {int flags; } ;

/* Variables and functions */
 int TCF_EM_CMP_TRANS ; 
 int unlikely (int) ; 

__attribute__((used)) static inline int cmp_needs_transformation(struct tcf_em_cmp *cmp)
{
	return unlikely(cmp->flags & TCF_EM_CMP_TRANS);
}