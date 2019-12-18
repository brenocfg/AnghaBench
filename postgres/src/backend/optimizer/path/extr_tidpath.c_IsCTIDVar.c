#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ varattno; scalar_t__ vartype; scalar_t__ varno; scalar_t__ varlevelsup; } ;
typedef  TYPE_1__ Var ;
struct TYPE_6__ {scalar_t__ relid; } ;
typedef  TYPE_2__ RelOptInfo ;

/* Variables and functions */
 scalar_t__ SelfItemPointerAttributeNumber ; 
 scalar_t__ TIDOID ; 

__attribute__((used)) static inline bool
IsCTIDVar(Var *var, RelOptInfo *rel)
{
	/* The vartype check is strictly paranoia */
	if (var->varattno == SelfItemPointerAttributeNumber &&
		var->vartype == TIDOID &&
		var->varno == rel->relid &&
		var->varlevelsup == 0)
		return true;
	return false;
}