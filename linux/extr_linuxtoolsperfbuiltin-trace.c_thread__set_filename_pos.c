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
struct TYPE_2__ {unsigned long ptr; char const* entry_str_pos; } ;
struct thread_trace {int entry_str; TYPE_1__ filename; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 struct thread_trace* thread__priv (struct thread*) ; 

__attribute__((used)) static void thread__set_filename_pos(struct thread *thread, const char *bf,
				     unsigned long ptr)
{
	struct thread_trace *ttrace = thread__priv(thread);

	ttrace->filename.ptr = ptr;
	ttrace->filename.entry_str_pos = bf - ttrace->entry_str;
}