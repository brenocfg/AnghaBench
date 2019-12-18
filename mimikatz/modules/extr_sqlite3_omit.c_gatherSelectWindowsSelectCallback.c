#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pSelect; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ Walker ;
typedef  int /*<<< orphan*/  Select ;

/* Variables and functions */
 int WRC_Continue ; 
 int WRC_Prune ; 

__attribute__((used)) static int gatherSelectWindowsSelectCallback(Walker *pWalker, Select *p){
  return p==pWalker->u.pSelect ? WRC_Continue : WRC_Prune;
}