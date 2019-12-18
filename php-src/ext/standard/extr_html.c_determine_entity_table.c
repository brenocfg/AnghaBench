#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  table; int /*<<< orphan*/  ms_table; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ entity_table_opt ;

/* Variables and functions */
 int ENT_HTML_DOC_HTML401 ; 
 int ENT_HTML_DOC_HTML5 ; 
 int ENT_HTML_DOC_XML1 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  entity_ms_table_html4 ; 
 int /*<<< orphan*/  entity_ms_table_html5 ; 
 int /*<<< orphan*/  stage3_table_be_apos_00000 ; 
 int /*<<< orphan*/  stage3_table_be_noapos_00000 ; 

__attribute__((used)) static entity_table_opt determine_entity_table(int all, int doctype)
{
	entity_table_opt retval = {NULL};

	assert(!(doctype == ENT_HTML_DOC_XML1 && all));

	if (all) {
		retval.ms_table = (doctype == ENT_HTML_DOC_HTML5) ?
			entity_ms_table_html5 : entity_ms_table_html4;
	} else {
		retval.table = (doctype == ENT_HTML_DOC_HTML401) ?
			stage3_table_be_noapos_00000 : stage3_table_be_apos_00000;
	}
	return retval;
}