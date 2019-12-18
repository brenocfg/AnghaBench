#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct mrb_time {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  enum mrb_timezone { ____Placeholder_mrb_timezone } mrb_timezone ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_to_time_t (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mrb_time* time_alloc_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct mrb_time*
time_alloc(mrb_state *mrb, mrb_value sec, mrb_value usec, enum mrb_timezone timezone)
{
  time_t tsec, tusec;

  tsec = mrb_to_time_t(mrb, sec, &tusec);
  tusec += mrb_to_time_t(mrb, usec, NULL);

  return time_alloc_time(mrb, tsec, tusec, timezone);
}