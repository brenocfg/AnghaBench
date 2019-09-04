#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct variable_list {int /*<<< orphan*/  vars; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  sp_die; int /*<<< orphan*/  machine; int /*<<< orphan*/  fb_ops; } ;
struct available_var_finder {int nvls; TYPE_1__ pf; scalar_t__ child; struct variable_list* vls; } ;
struct TYPE_4__ {scalar_t__ show_location_range; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DIE_FIND_CB_CONTINUE ; 
 int DIE_FIND_CB_END ; 
 int DIE_FIND_CB_SIBLING ; 
 int DW_TAG_formal_parameter ; 
 int DW_TAG_variable ; 
 int ERANGE ; 
 struct strbuf STRBUF_INIT ; 
 int convert_variable_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int die_get_var_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct strbuf*) ; 
 int die_get_varname (int /*<<< orphan*/ *,struct strbuf*) ; 
 scalar_t__ dwarf_haspc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwarf_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 TYPE_2__ probe_conf ; 
 int strbuf_add (struct strbuf*,char*,int) ; 
 scalar_t__ strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strlist__add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int collect_variables_cb(Dwarf_Die *die_mem, void *data)
{
	struct available_var_finder *af = data;
	struct variable_list *vl;
	struct strbuf buf = STRBUF_INIT;
	int tag, ret;

	vl = &af->vls[af->nvls - 1];

	tag = dwarf_tag(die_mem);
	if (tag == DW_TAG_formal_parameter ||
	    tag == DW_TAG_variable) {
		ret = convert_variable_location(die_mem, af->pf.addr,
						af->pf.fb_ops, &af->pf.sp_die,
						af->pf.machine, NULL);
		if (ret == 0 || ret == -ERANGE) {
			int ret2;
			bool externs = !af->child;

			if (strbuf_init(&buf, 64) < 0)
				goto error;

			if (probe_conf.show_location_range) {
				if (!externs)
					ret2 = strbuf_add(&buf,
						ret ? "[INV]\t" : "[VAL]\t", 6);
				else
					ret2 = strbuf_add(&buf, "[EXT]\t", 6);
				if (ret2)
					goto error;
			}

			ret2 = die_get_varname(die_mem, &buf);

			if (!ret2 && probe_conf.show_location_range &&
				!externs) {
				if (strbuf_addch(&buf, '\t') < 0)
					goto error;
				ret2 = die_get_var_range(&af->pf.sp_die,
							die_mem, &buf);
			}

			pr_debug("Add new var: %s\n", buf.buf);
			if (ret2 == 0) {
				strlist__add(vl->vars,
					strbuf_detach(&buf, NULL));
			}
			strbuf_release(&buf);
		}
	}

	if (af->child && dwarf_haspc(die_mem, af->pf.addr))
		return DIE_FIND_CB_CONTINUE;
	else
		return DIE_FIND_CB_SIBLING;
error:
	strbuf_release(&buf);
	pr_debug("Error in strbuf\n");
	return DIE_FIND_CB_END;
}