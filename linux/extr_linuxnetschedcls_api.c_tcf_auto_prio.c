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
typedef  scalar_t__ u32 ;
struct tcf_proto {scalar_t__ prio; } ;

/* Variables and functions */
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_MAKE (int,unsigned int) ; 

__attribute__((used)) static inline u32 tcf_auto_prio(struct tcf_proto *tp)
{
	u32 first = TC_H_MAKE(0xC0000000U, 0U);

	if (tp)
		first = tp->prio - 1;

	return TC_H_MAJ(first);
}