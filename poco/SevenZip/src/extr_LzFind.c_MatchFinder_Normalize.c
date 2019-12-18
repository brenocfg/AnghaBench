#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_5__ {scalar_t__ numSons; scalar_t__ hashSizeSum; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  MatchFinder_GetSubValue (TYPE_1__*) ; 
 int /*<<< orphan*/  MatchFinder_Normalize3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MatchFinder_ReduceOffsets (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MatchFinder_Normalize(CMatchFinder *p)
{
  UInt32 subValue = MatchFinder_GetSubValue(p);
  MatchFinder_Normalize3(subValue, p->hash, p->hashSizeSum + p->numSons);
  MatchFinder_ReduceOffsets(p, subValue);
}