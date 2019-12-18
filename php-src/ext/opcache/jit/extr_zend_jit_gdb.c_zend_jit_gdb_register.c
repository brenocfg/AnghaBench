#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  line_start; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ zend_op_array ;
struct TYPE_6__ {uintptr_t mcaddr; char const* name; char* filename; int /*<<< orphan*/  objsize; int /*<<< orphan*/  obj; int /*<<< orphan*/  lineno; scalar_t__ szmcode; } ;
typedef  TYPE_2__ zend_gdbjit_ctx ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 char* ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int zend_gdb_register_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_gdbjit_buildobj (TYPE_2__*) ; 

__attribute__((used)) static int zend_jit_gdb_register(const char    *name,
                                 const zend_op_array *op_array,
                                 const void    *start,
                                 size_t         size)
{
	zend_gdbjit_ctx ctx;

	ctx.mcaddr = (uintptr_t)start;
	ctx.szmcode = (uint32_t)size;
	ctx.name = name;
	ctx.filename = op_array ? ZSTR_VAL(op_array->filename) : "unknown";
	ctx.lineno = op_array ? op_array->line_start : 0;

	zend_gdbjit_buildobj(&ctx);

	return zend_gdb_register_code(&ctx.obj, ctx.objsize);
}