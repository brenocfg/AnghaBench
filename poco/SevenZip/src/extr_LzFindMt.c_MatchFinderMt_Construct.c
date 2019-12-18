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
struct TYPE_3__ {int /*<<< orphan*/  btSync; int /*<<< orphan*/  hashSync; scalar_t__ hashBuf; } ;
typedef  TYPE_1__ CMatchFinderMt ;

/* Variables and functions */
 int /*<<< orphan*/  MtSync_Construct (int /*<<< orphan*/ *) ; 

void MatchFinderMt_Construct(CMatchFinderMt *p)
{
  p->hashBuf = 0;
  MtSync_Construct(&p->hashSync);
  MtSync_Construct(&p->btSync);
}