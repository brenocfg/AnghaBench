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
struct bwriter_shader {int /*<<< orphan*/  num_cf; int /*<<< orphan*/  constF; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DSIO_DEF ; 
 int /*<<< orphan*/  D3DSPR_CONST ; 
 int /*<<< orphan*/  write_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bytecode_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_constF(const struct bwriter_shader *shader, struct bytecode_buffer *buffer, BOOL len) {
    write_const(shader->constF, shader->num_cf, D3DSIO_DEF, D3DSPR_CONST, buffer, len);
}