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
struct thread {int dummy; } ;
struct machine {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct thread* ____machine__findnew_thread (struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  machine__threads (struct machine*,int /*<<< orphan*/ ) ; 

struct thread *__machine__findnew_thread(struct machine *machine, pid_t pid, pid_t tid)
{
	return ____machine__findnew_thread(machine, machine__threads(machine, tid), pid, tid, true);
}