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
struct TYPE_3__ {int len; } ;
struct hpp_dynamic_entry {int dynamic_len; TYPE_1__ hpp; TYPE_2__* field; } ;
struct TYPE_4__ {int size; int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int TEP_FIELD_IS_STRING ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hde_width(struct hpp_dynamic_entry *hde)
{
	if (!hde->hpp.len) {
		int len = hde->dynamic_len;
		int namelen = strlen(hde->field->name);
		int fieldlen = hde->field->size;

		if (namelen > len)
			len = namelen;

		if (!(hde->field->flags & TEP_FIELD_IS_STRING)) {
			/* length for print hex numbers */
			fieldlen = hde->field->size * 2 + 2;
		}
		if (fieldlen > len)
			len = fieldlen;

		hde->hpp.len = len;
	}
	return hde->hpp.len;
}