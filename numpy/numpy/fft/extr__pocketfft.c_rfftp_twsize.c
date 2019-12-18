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
typedef  TYPE_2__* rfftp_plan ;
struct TYPE_5__ {size_t nfct; size_t length; TYPE_1__* fct; } ;
struct TYPE_4__ {size_t fct; } ;

/* Variables and functions */

__attribute__((used)) static size_t rfftp_twsize(rfftp_plan plan)
  {
  size_t twsize=0, l1=1;
  for (size_t k=0; k<plan->nfct; ++k)
    {
    size_t ip=plan->fct[k].fct, ido= plan->length/(l1*ip);
    twsize+=(ip-1)*(ido-1);
    if (ip>5) twsize+=2*ip;
    l1*=ip;
    }
  return twsize;
  return 0;
  }