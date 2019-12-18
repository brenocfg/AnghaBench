#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_4__ {int* crc; scalar_t__ hash; scalar_t__ directInput; scalar_t__ bufferBase; } ;
typedef  TYPE_1__ CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  MatchFinder_SetDefaultSettings (TYPE_1__*) ; 
 int kCrcPoly ; 

void MatchFinder_Construct(CMatchFinder *p)
{
  UInt32 i;
  p->bufferBase = 0;
  p->directInput = 0;
  p->hash = 0;
  MatchFinder_SetDefaultSettings(p);

  for (i = 0; i < 256; i++)
  {
    UInt32 r = i;
    int j;
    for (j = 0; j < 8; j++)
      r = (r >> 1) ^ (kCrcPoly & ~((r & 1) - 1));
    p->crc[i] = r;
  }
}