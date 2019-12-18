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
struct TYPE_3__ {size_t capacity; int /*<<< orphan*/  read_data; } ;
typedef  TYPE_1__ ipc_pipe_server_t ;

/* Variables and functions */
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void ipc_pipe_internal_ensure_capacity(ipc_pipe_server_t *pipe,
						     size_t new_size)
{
	if (pipe->capacity >= new_size) {
		return;
	}

	pipe->read_data = realloc(pipe->read_data, new_size);
	pipe->capacity = new_size;
}