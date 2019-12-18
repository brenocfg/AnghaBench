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
struct TYPE_2__ {int /*<<< orphan*/  (* ctl ) (struct event_set*,int /*<<< orphan*/ ,unsigned int,void*) ;} ;
struct event_set {TYPE_1__ func; } ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct event_set*,int /*<<< orphan*/ ,unsigned int,void*) ; 

__attribute__((used)) static inline void
event_ctl(struct event_set *es, event_t event, unsigned int rwflags, void *arg)
{
    (*es->func.ctl)(es, event, rwflags, arg);
}