#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * output; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ xmlwriter_object ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlBufferFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeTextWriter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xmlwriter_free_resource_ptr(xmlwriter_object *intern)
{
	if (intern) {
		if (intern->ptr) {
			xmlFreeTextWriter(intern->ptr);
			intern->ptr = NULL;
		}
		if (intern->output) {
			xmlBufferFree(intern->output);
			intern->output = NULL;
		}
		efree(intern);
	}
}