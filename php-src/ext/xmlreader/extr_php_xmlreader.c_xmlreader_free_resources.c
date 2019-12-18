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
struct TYPE_3__ {int /*<<< orphan*/ * schema; int /*<<< orphan*/ * ptr; int /*<<< orphan*/ * input; } ;
typedef  TYPE_1__ xmlreader_object ;
typedef  int /*<<< orphan*/  xmlRelaxNGPtr ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFreeParserInputBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeTextReader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlRelaxNGFree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xmlreader_free_resources(xmlreader_object *intern) {
	if (intern) {
		if (intern->input) {
			xmlFreeParserInputBuffer(intern->input);
			intern->input = NULL;
		}

		if (intern->ptr) {
			xmlFreeTextReader(intern->ptr);
			intern->ptr = NULL;
		}
#ifdef LIBXML_SCHEMAS_ENABLED
		if (intern->schema) {
			xmlRelaxNGFree((xmlRelaxNGPtr) intern->schema);
			intern->schema = NULL;
		}
#endif
	}
}