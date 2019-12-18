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
struct thread {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid_; } ;
struct TYPE_2__ {scalar_t__ tid_list; scalar_t__ pid_list; scalar_t__ comm_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  intlist__has_entry (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlist__has_entry (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  thread__comm_str (struct thread*) ; 

__attribute__((used)) static inline bool thread__is_filtered(struct thread *thread)
{
	if (symbol_conf.comm_list &&
	    !strlist__has_entry(symbol_conf.comm_list, thread__comm_str(thread))) {
		return true;
	}

	if (symbol_conf.pid_list &&
	    !intlist__has_entry(symbol_conf.pid_list, thread->pid_)) {
		return true;
	}

	if (symbol_conf.tid_list &&
	    !intlist__has_entry(symbol_conf.tid_list, thread->tid)) {
		return true;
	}

	return false;
}