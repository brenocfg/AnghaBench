#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct element {int flags; int compound; size_t class; size_t method; int tag; int entry_index; TYPE_4__* action; struct element* next; struct element* children; struct element* render_next; TYPE_6__* type_def; TYPE_3__* type; TYPE_1__* name; } ;
struct TYPE_12__ {int ref_count; TYPE_5__* name; } ;
struct TYPE_11__ {int /*<<< orphan*/  content; } ;
struct TYPE_10__ {int name; } ;
struct TYPE_9__ {TYPE_2__* type; } ;
struct TYPE_8__ {struct element* element; } ;
struct TYPE_7__ {int /*<<< orphan*/  content; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  ANY 135 
 size_t ASN1_PRIM ; 
 size_t ASN1_UNIV ; 
#define  CHOICE 134 
 int ELEMENT_CONDITIONAL ; 
 int ELEMENT_RENDERED ; 
 int ELEMENT_SKIPPABLE ; 
 int ELEMENT_TAG_SPECIFIED ; 
#define  SEQUENCE 133 
#define  SEQUENCE_OF 132 
#define  SET 131 
#define  SET_OF 130 
#define  TAG_OVERRIDE 129 
#define  TYPE_REF 128 
 int /*<<< orphan*/ * asn1_classes ; 
 int /*<<< orphan*/ * asn1_methods ; 
 int /*<<< orphan*/ * asn1_universal_tags ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int nr_entries ; 
 int /*<<< orphan*/  render_depth ; 
 struct element** render_list_p ; 
 int /*<<< orphan*/  render_more (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  render_opcode (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void render_element(FILE *out, struct element *e, struct element *tag)
{
	struct element *ec, *x;
	const char *cond, *act;
	int entry, skippable = 0, outofline = 0;

	if (e->flags & ELEMENT_SKIPPABLE ||
	    (tag && tag->flags & ELEMENT_SKIPPABLE))
		skippable = 1;

	if ((e->type_def && e->type_def->ref_count > 1) ||
	    skippable)
		outofline = 1;

	if (e->type_def && out) {
		render_more(out, "\t// %s\n", e->type_def->name->content);
	}

	/* Render the operation */
	cond = (e->flags & ELEMENT_CONDITIONAL ||
		(tag && tag->flags & ELEMENT_CONDITIONAL)) ? "COND_" : "";
	act = e->action ? "_ACT" : "";
	switch (e->compound) {
	case ANY:
		render_opcode(out, "ASN1_OP_%sMATCH_ANY%s%s,",
			      cond, act, skippable ? "_OR_SKIP" : "");
		if (e->name)
			render_more(out, "\t\t// %s", e->name->content);
		render_more(out, "\n");
		goto dont_render_tag;

	case TAG_OVERRIDE:
		render_element(out, e->children, e);
		return;

	case SEQUENCE:
	case SEQUENCE_OF:
	case SET:
	case SET_OF:
		render_opcode(out, "ASN1_OP_%sMATCH%s%s,",
			      cond,
			      outofline ? "_JUMP" : "",
			      skippable ? "_OR_SKIP" : "");
		break;

	case CHOICE:
		goto dont_render_tag;

	case TYPE_REF:
		if (e->class == ASN1_UNIV && e->method == ASN1_PRIM && e->tag == 0)
			goto dont_render_tag;
	default:
		render_opcode(out, "ASN1_OP_%sMATCH%s%s,",
			      cond, act,
			      skippable ? "_OR_SKIP" : "");
		break;
	}

	x = tag ?: e;
	if (x->name)
		render_more(out, "\t\t// %s", x->name->content);
	render_more(out, "\n");

	/* Render the tag */
	if (!tag || !(tag->flags & ELEMENT_TAG_SPECIFIED))
		tag = e;

	if (tag->class == ASN1_UNIV &&
	    tag->tag != 14 &&
	    tag->tag != 15 &&
	    tag->tag != 31)
		render_opcode(out, "_tag(%s, %s, %s),\n",
			      asn1_classes[tag->class],
			      asn1_methods[tag->method | e->method],
			      asn1_universal_tags[tag->tag]);
	else
		render_opcode(out, "_tagn(%s, %s, %2u),\n",
			      asn1_classes[tag->class],
			      asn1_methods[tag->method | e->method],
			      tag->tag);
	tag = NULL;
dont_render_tag:

	/* Deal with compound types */
	switch (e->compound) {
	case TYPE_REF:
		render_element(out, e->type->type->element, tag);
		if (e->action)
			render_opcode(out, "ASN1_OP_%sACT,\n",
				      skippable ? "MAYBE_" : "");
		break;

	case SEQUENCE:
		if (outofline) {
			/* Render out-of-line for multiple use or
			 * skipability */
			render_opcode(out, "_jump_target(%u),", e->entry_index);
			if (e->type_def && e->type_def->name)
				render_more(out, "\t\t// --> %s",
					    e->type_def->name->content);
			render_more(out, "\n");
			if (!(e->flags & ELEMENT_RENDERED)) {
				e->flags |= ELEMENT_RENDERED;
				*render_list_p = e;
				render_list_p = &e->render_next;
			}
			return;
		} else {
			/* Render inline for single use */
			render_depth++;
			for (ec = e->children; ec; ec = ec->next)
				render_element(out, ec, NULL);
			render_depth--;
			render_opcode(out, "ASN1_OP_END_SEQ%s,\n", act);
		}
		break;

	case SEQUENCE_OF:
	case SET_OF:
		if (outofline) {
			/* Render out-of-line for multiple use or
			 * skipability */
			render_opcode(out, "_jump_target(%u),", e->entry_index);
			if (e->type_def && e->type_def->name)
				render_more(out, "\t\t// --> %s",
					    e->type_def->name->content);
			render_more(out, "\n");
			if (!(e->flags & ELEMENT_RENDERED)) {
				e->flags |= ELEMENT_RENDERED;
				*render_list_p = e;
				render_list_p = &e->render_next;
			}
			return;
		} else {
			/* Render inline for single use */
			entry = nr_entries;
			render_depth++;
			render_element(out, e->children, NULL);
			render_depth--;
			if (e->compound == SEQUENCE_OF)
				render_opcode(out, "ASN1_OP_END_SEQ_OF%s,\n", act);
			else
				render_opcode(out, "ASN1_OP_END_SET_OF%s,\n", act);
			render_opcode(out, "_jump_target(%u),\n", entry);
		}
		break;

	case SET:
		/* I can't think of a nice way to do SET support without having
		 * a stack of bitmasks to make sure no element is repeated.
		 * The bitmask has also to be checked that no non-optional
		 * elements are left out whilst not preventing optional
		 * elements from being left out.
		 */
		fprintf(stderr, "The ASN.1 SET type is not currently supported.\n");
		exit(1);

	case CHOICE:
		for (ec = e->children; ec; ec = ec->next)
			render_element(out, ec, ec);
		if (!skippable)
			render_opcode(out, "ASN1_OP_COND_FAIL,\n");
		if (e->action)
			render_opcode(out, "ASN1_OP_ACT,\n");
		break;

	default:
		break;
	}

	if (e->action)
		render_opcode(out, "_action(ACT_%s),\n", e->action->name);
}