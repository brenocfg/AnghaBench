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
struct snd_rawmidi_runtime {int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  avail; scalar_t__ hw_ptr; scalar_t__ appl_ptr; scalar_t__ drain; } ;

/* Variables and functions */

__attribute__((used)) static void __reset_runtime_ptrs(struct snd_rawmidi_runtime *runtime,
				 bool is_input)
{
	runtime->drain = 0;
	runtime->appl_ptr = runtime->hw_ptr = 0;
	runtime->avail = is_input ? 0 : runtime->buffer_size;
}