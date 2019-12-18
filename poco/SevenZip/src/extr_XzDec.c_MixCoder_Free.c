#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* Free ) (TYPE_3__*,scalar_t__) ;} ;
struct TYPE_7__ {int numCoders; scalar_t__ buf; TYPE_3__* alloc; TYPE_1__* coders; } ;
struct TYPE_6__ {scalar_t__ p; int /*<<< orphan*/  (* Free ) (scalar_t__,TYPE_3__*) ;} ;
typedef  TYPE_1__ IStateCoder ;
typedef  TYPE_2__ CMixCoder ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,scalar_t__) ; 

void MixCoder_Free(CMixCoder *p)
{
  int i;
  for (i = 0; i < p->numCoders; i++)
  {
    IStateCoder *sc = &p->coders[i];
    if (p->alloc && sc->p)
      sc->Free(sc->p, p->alloc);
  }
  p->numCoders = 0;
  if (p->buf)
    p->alloc->Free(p->alloc, p->buf);
}