#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct event_set_return {int dummy; } ;
struct TYPE_2__ {int (* wait ) (struct event_set*,struct timeval const*,struct event_set_return*,int) ;} ;
struct event_set {TYPE_1__ func; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_IO_WAIT ; 
 int /*<<< orphan*/  perf_pop () ; 
 int /*<<< orphan*/  perf_push (int /*<<< orphan*/ ) ; 
 int stub1 (struct event_set*,struct timeval const*,struct event_set_return*,int) ; 

__attribute__((used)) static inline int
event_wait(struct event_set *es, const struct timeval *tv, struct event_set_return *out, int outlen)
{
    int ret;
    perf_push(PERF_IO_WAIT);
    ret = (*es->func.wait)(es, tv, out, outlen);
    perf_pop();
    return ret;
}