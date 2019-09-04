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
struct TYPE_4__ {int /*<<< orphan*/  top; int /*<<< orphan*/  language; } ;
typedef  TYPE_1__ lookup_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_node_destroy (int /*<<< orphan*/ ) ; 

void text_lookup_destroy(lookup_t *lookup)
{
	if (lookup) {
		dstr_free(&lookup->language);
		text_node_destroy(lookup->top);

		bfree(lookup);
	}
}