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
typedef  int u16 ;
struct echoaudio {int pipe_alloc_mask; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_pipe_allocated(struct echoaudio *chip, u16 pipe_index)
{
	return (chip->pipe_alloc_mask & (1 << pipe_index));
}