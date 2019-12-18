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
struct TYPE_5__ {scalar_t__ nOBSat; scalar_t__ nRow; } ;
struct TYPE_6__ {scalar_t__ rCost; TYPE_1__ plan; } ;
typedef  TYPE_2__ WhereCost ;

/* Variables and functions */

__attribute__((used)) static int compareCost(const WhereCost *pProbe, const WhereCost *pBaseline){
  if( pProbe->rCost<pBaseline->rCost ) return 1;
  if( pProbe->rCost>pBaseline->rCost ) return 0;
  if( pProbe->plan.nOBSat>pBaseline->plan.nOBSat ) return 1;
  if( pProbe->plan.nRow<pBaseline->plan.nRow ) return 1;
  return 0;
}