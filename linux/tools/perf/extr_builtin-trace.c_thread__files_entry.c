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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  thread__priv (struct thread*) ; 
 struct file* thread_trace__files_entry (int /*<<< orphan*/ ,int) ; 

struct file *thread__files_entry(struct thread *thread, int fd)
{
	return thread_trace__files_entry(thread__priv(thread), fd);
}