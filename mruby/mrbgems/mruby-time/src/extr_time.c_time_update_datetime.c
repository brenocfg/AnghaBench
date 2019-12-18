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
struct tm {int dummy; } ;
struct mrb_time {scalar_t__ timezone; struct tm datetime; int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_sec ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 scalar_t__ MRB_TIMEZONE_UTC ; 
 struct tm* gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 struct tm* localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,struct mrb_time*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sec_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mrb_time*
time_update_datetime(mrb_state *mrb, struct mrb_time *self, int dealloc)
{
  struct tm *aid;
  time_t t = self->sec;

  if (self->timezone == MRB_TIMEZONE_UTC) {
    aid = gmtime_r(&t, &self->datetime);
  }
  else {
    aid = localtime_r(&t, &self->datetime);
  }
  if (!aid) {
    mrb_sec sec = (mrb_sec)t;

    if (dealloc) mrb_free(mrb, self);
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "%v out of Time range", mrb_sec_value(mrb, sec));
    /* not reached */
    return NULL;
  }
#ifdef NO_GMTIME_R
  self->datetime = *aid; /* copy data */
#endif

  return self;
}