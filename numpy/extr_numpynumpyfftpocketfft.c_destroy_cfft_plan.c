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
typedef  TYPE_1__* cfft_plan ;
struct TYPE_4__ {scalar_t__ packplan; scalar_t__ blueplan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_cfftp_plan (scalar_t__) ; 
 int /*<<< orphan*/  destroy_fftblue_plan (scalar_t__) ; 

__attribute__((used)) static void destroy_cfft_plan (cfft_plan plan)
  {
  if (plan->blueplan)
    destroy_fftblue_plan(plan->blueplan);
  if (plan->packplan)
    destroy_cfftp_plan(plan->packplan);
  DEALLOC(plan);
  }