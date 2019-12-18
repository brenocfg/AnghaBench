#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ wsFlags; int /*<<< orphan*/  aLTermSpace; int /*<<< orphan*/  nLSlot; scalar_t__ nLTerm; int /*<<< orphan*/  aLTerm; } ;
typedef  TYPE_1__ WhereLoop ;

/* Variables and functions */
 int /*<<< orphan*/  ArraySize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void whereLoopInit(WhereLoop *p){
  p->aLTerm = p->aLTermSpace;
  p->nLTerm = 0;
  p->nLSlot = ArraySize(p->aLTermSpace);
  p->wsFlags = 0;
}