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
struct TYPE_5__ {int Code; int Range; TYPE_1__* Stream; } ;
struct TYPE_4__ {int (* Read ) (void*) ;} ;
typedef  TYPE_2__ CPpmd7z_RangeDec ;
typedef  int Bool ;

/* Variables and functions */
 int False ; 
 int stub1 (void*) ; 
 int stub2 (void*) ; 

Bool Ppmd7z_RangeDec_Init(CPpmd7z_RangeDec *p)
{
  unsigned i;
  p->Code = 0;
  p->Range = 0xFFFFFFFF;
  if (p->Stream->Read((void *)p->Stream) != 0)
    return False;
  for (i = 0; i < 4; i++)
    p->Code = (p->Code << 8) | p->Stream->Read((void *)p->Stream);
  return (p->Code < 0xFFFFFFFF);
}