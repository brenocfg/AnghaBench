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
struct cf_ctrset_entry {scalar_t__ def; } ;

/* Variables and functions */
 scalar_t__ S390_CPUMCF_DIAG_DEF ; 

__attribute__((used)) static bool ctrset_valid(struct cf_ctrset_entry *set)
{
	return set->def == S390_CPUMCF_DIAG_DEF;
}