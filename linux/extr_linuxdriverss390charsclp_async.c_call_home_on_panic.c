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
struct notifier_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 TYPE_1__* init_utsname () ; 
 int /*<<< orphan*/  sclp_async_send_wait (void*) ; 
 int /*<<< orphan*/  strncat (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int call_home_on_panic(struct notifier_block *self,
			      unsigned long event, void *data)
{
	strncat(data, init_utsname()->nodename,
		sizeof(init_utsname()->nodename));
	sclp_async_send_wait(data);
	return NOTIFY_DONE;
}