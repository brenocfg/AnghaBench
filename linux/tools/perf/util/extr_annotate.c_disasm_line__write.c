#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* ops; } ;
struct TYPE_13__ {scalar_t__ offset; } ;
struct TYPE_11__ {scalar_t__ offset; scalar_t__ outside; } ;
struct TYPE_12__ {TYPE_2__ target; } ;
struct disasm_line {TYPE_7__ ins; TYPE_4__ al; TYPE_3__ ops; } ;
struct TYPE_15__ {int /*<<< orphan*/  max_ins_name; } ;
struct annotation {TYPE_6__ widths; TYPE_5__* options; } ;
struct TYPE_14__ {int /*<<< orphan*/  use_offset; } ;
struct TYPE_10__ {scalar_t__ scnprintf; } ;

/* Variables and functions */
 int DARROW_CHAR ; 
 int LARROW_CHAR ; 
 int RARROW_CHAR ; 
 int UARROW_CHAR ; 
 int /*<<< orphan*/  disasm_line__scnprintf (struct disasm_line*,char*,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ins__is_call (TYPE_7__*) ; 
 scalar_t__ ins__is_jump (TYPE_7__*) ; 
 scalar_t__ ins__is_ret (TYPE_7__*) ; 

__attribute__((used)) static void disasm_line__write(struct disasm_line *dl, struct annotation *notes,
			       void *obj, char *bf, size_t size,
			       void (*obj__printf)(void *obj, const char *fmt, ...),
			       void (*obj__write_graph)(void *obj, int graph))
{
	if (dl->ins.ops && dl->ins.ops->scnprintf) {
		if (ins__is_jump(&dl->ins)) {
			bool fwd;

			if (dl->ops.target.outside)
				goto call_like;
			fwd = dl->ops.target.offset > dl->al.offset;
			obj__write_graph(obj, fwd ? DARROW_CHAR : UARROW_CHAR);
			obj__printf(obj, " ");
		} else if (ins__is_call(&dl->ins)) {
call_like:
			obj__write_graph(obj, RARROW_CHAR);
			obj__printf(obj, " ");
		} else if (ins__is_ret(&dl->ins)) {
			obj__write_graph(obj, LARROW_CHAR);
			obj__printf(obj, " ");
		} else {
			obj__printf(obj, "  ");
		}
	} else {
		obj__printf(obj, "  ");
	}

	disasm_line__scnprintf(dl, bf, size, !notes->options->use_offset, notes->widths.max_ins_name);
}