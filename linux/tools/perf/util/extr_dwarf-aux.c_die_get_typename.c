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
struct strbuf {int dummy; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DW_TAG_array_type ; 
 int DW_TAG_enumeration_type ; 
 int DW_TAG_pointer_type ; 
 int DW_TAG_structure_type ; 
 int DW_TAG_subroutine_type ; 
 int DW_TAG_union_type ; 
 int ENOENT ; 
 int /*<<< orphan*/ * __die_get_real_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_diename (int /*<<< orphan*/ *) ; 
 int dwarf_tag (int /*<<< orphan*/ *) ; 
 int strbuf_add (struct strbuf*,char*,int) ; 
 int strbuf_addf (struct strbuf*,char*,char const*,int /*<<< orphan*/ ) ; 
 int strbuf_addstr (struct strbuf*,char const*) ; 

int die_get_typename(Dwarf_Die *vr_die, struct strbuf *buf)
{
	Dwarf_Die type;
	int tag, ret;
	const char *tmp = "";

	if (__die_get_real_type(vr_die, &type) == NULL)
		return -ENOENT;

	tag = dwarf_tag(&type);
	if (tag == DW_TAG_array_type || tag == DW_TAG_pointer_type)
		tmp = "*";
	else if (tag == DW_TAG_subroutine_type) {
		/* Function pointer */
		return strbuf_add(buf, "(function_type)", 15);
	} else {
		if (!dwarf_diename(&type))
			return -ENOENT;
		if (tag == DW_TAG_union_type)
			tmp = "union ";
		else if (tag == DW_TAG_structure_type)
			tmp = "struct ";
		else if (tag == DW_TAG_enumeration_type)
			tmp = "enum ";
		/* Write a base name */
		return strbuf_addf(buf, "%s%s", tmp, dwarf_diename(&type));
	}
	ret = die_get_typename(&type, buf);
	return ret ? ret : strbuf_addstr(buf, tmp);
}