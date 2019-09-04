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
struct element {int entry_index; int compound; TYPE_1__* action; struct element* next; struct element* children; struct element* render_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  SEQUENCE 131 
#define  SEQUENCE_OF 130 
#define  SET 129 
#define  SET_OF 128 
 int nr_entries ; 
 int /*<<< orphan*/  render_depth ; 
 int /*<<< orphan*/  render_element (int /*<<< orphan*/ *,struct element*,int /*<<< orphan*/ *) ; 
 struct element* render_list ; 
 struct element** render_list_p ; 
 int /*<<< orphan*/  render_more (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  render_opcode (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void render_out_of_line_list(FILE *out)
{
	struct element *e, *ce;
	const char *act;
	int entry;

	while ((e = render_list)) {
		render_list = e->render_next;
		if (!render_list)
			render_list_p = &render_list;

		render_more(out, "\n");
		e->entry_index = entry = nr_entries;
		render_depth++;
		for (ce = e->children; ce; ce = ce->next)
			render_element(out, ce, NULL);
		render_depth--;

		act = e->action ? "_ACT" : "";
		switch (e->compound) {
		case SEQUENCE:
			render_opcode(out, "ASN1_OP_END_SEQ%s,\n", act);
			break;
		case SEQUENCE_OF:
			render_opcode(out, "ASN1_OP_END_SEQ_OF%s,\n", act);
			render_opcode(out, "_jump_target(%u),\n", entry);
			break;
		case SET:
			render_opcode(out, "ASN1_OP_END_SET%s,\n", act);
			break;
		case SET_OF:
			render_opcode(out, "ASN1_OP_END_SET_OF%s,\n", act);
			render_opcode(out, "_jump_target(%u),\n", entry);
			break;
		default:
			break;
		}
		if (e->action)
			render_opcode(out, "_action(ACT_%s),\n",
				      e->action->name);
		render_opcode(out, "ASN1_OP_RETURN,\n");
	}
}