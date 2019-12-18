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
struct gs_program {int dummy; } ;
struct gs_device {int dummy; } ;

/* Variables and functions */
 struct gs_program* find_program (struct gs_device*) ; 
 struct gs_program* gs_program_create (struct gs_device*) ; 

__attribute__((used)) static inline struct gs_program *get_shader_program(struct gs_device *device)
{
	struct gs_program *program = find_program(device);

	if (!program)
		program = gs_program_create(device);

	return program;
}