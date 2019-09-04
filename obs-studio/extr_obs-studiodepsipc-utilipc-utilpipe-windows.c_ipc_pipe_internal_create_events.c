#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ready_event; } ;
typedef  TYPE_1__ ipc_pipe_server_t ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEvent (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool ipc_pipe_internal_create_events(ipc_pipe_server_t *pipe)
{
	pipe->ready_event = CreateEvent(NULL, false, false, NULL);
	return !!pipe->ready_event;
}