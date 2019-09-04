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
struct bytecode_buffer {int dummy; } ;
struct bwriter_shader {int /*<<< orphan*/  num_outputs; int /*<<< orphan*/  outputs; int /*<<< orphan*/  num_inputs; int /*<<< orphan*/  inputs; } ;
struct bc_writer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWRITERSPR_INPUT ; 
 int /*<<< orphan*/  BWRITERSPR_OUTPUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  write_constB (struct bwriter_shader const*,struct bytecode_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_constF (struct bwriter_shader const*,struct bytecode_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_constI (struct bwriter_shader const*,struct bytecode_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_declarations (struct bc_writer*,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_samplers (struct bwriter_shader const*,struct bytecode_buffer*) ; 

__attribute__((used)) static void sm_3_header(struct bc_writer *This, const struct bwriter_shader *shader, struct bytecode_buffer *buffer) {
    write_declarations(This, buffer, TRUE, shader->inputs, shader->num_inputs, BWRITERSPR_INPUT);
    write_declarations(This, buffer, TRUE, shader->outputs, shader->num_outputs, BWRITERSPR_OUTPUT);
    write_constF(shader, buffer, TRUE);
    write_constB(shader, buffer, TRUE);
    write_constI(shader, buffer, TRUE);
    write_samplers(shader, buffer);
}