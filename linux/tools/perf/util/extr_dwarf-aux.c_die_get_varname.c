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
 int die_get_typename (int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  dwarf_diename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int strbuf_add (struct strbuf*,char*,int) ; 
 int strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 

int die_get_varname(Dwarf_Die *vr_die, struct strbuf *buf)
{
	int ret;

	ret = die_get_typename(vr_die, buf);
	if (ret < 0) {
		pr_debug("Failed to get type, make it unknown.\n");
		ret = strbuf_add(buf, " (unknown_type)", 14);
	}

	return ret < 0 ? ret : strbuf_addf(buf, "\t%s", dwarf_diename(vr_die));
}