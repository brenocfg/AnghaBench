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
struct pid {int dummy; } ;

/* Variables and functions */
 struct pid* get_pid (struct pid*) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 

__attribute__((used)) static inline void ipc_update_pid(struct pid **pos, struct pid *pid)
{
	struct pid *old = *pos;
	if (old != pid) {
		*pos = get_pid(pid);
		put_pid(old);
	}
}