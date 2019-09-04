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
typedef  TYPE_1__* cfft_plan ;
struct TYPE_5__ {void* packplan; scalar_t__ blueplan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEALLOC (TYPE_1__*) ; 
 TYPE_1__* RALLOC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfft_plan_i ; 
 int cost_guess (size_t) ; 
 size_t good_size (int) ; 
 scalar_t__ largest_prime_factor (size_t) ; 
 void* make_cfftp_plan (size_t) ; 
 scalar_t__ make_fftblue_plan (size_t) ; 
 scalar_t__ sqrt (size_t) ; 

__attribute__((used)) static cfft_plan make_cfft_plan (size_t length)
  {
  if (length==0) return NULL;
  cfft_plan plan = RALLOC(cfft_plan_i,1);
  if (!plan) return NULL;
  plan->blueplan=0;
  plan->packplan=0;
  if ((length<50) || (largest_prime_factor(length)<=sqrt(length)))
    {
    plan->packplan=make_cfftp_plan(length);
    if (!plan->packplan) { DEALLOC(plan); return NULL; }
    return plan;
    }
  double comp1 = cost_guess(length);
  double comp2 = 2*cost_guess(good_size(2*length-1));
  comp2*=1.5; /* fudge factor that appears to give good overall performance */
  if (comp2<comp1) // use Bluestein
    {
    plan->blueplan=make_fftblue_plan(length);
    if (!plan->blueplan) { DEALLOC(plan); return NULL; }
    }
  else
    {
    plan->packplan=make_cfftp_plan(length);
    if (!plan->packplan) { DEALLOC(plan); return NULL; }
    }
  return plan;
  }