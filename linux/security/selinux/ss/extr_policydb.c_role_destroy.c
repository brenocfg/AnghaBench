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
struct role_datum {int /*<<< orphan*/  types; int /*<<< orphan*/  dominates; } ;

/* Variables and functions */
 int /*<<< orphan*/  ebitmap_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static int role_destroy(void *key, void *datum, void *p)
{
	struct role_datum *role;

	kfree(key);
	if (datum) {
		role = datum;
		ebitmap_destroy(&role->dominates);
		ebitmap_destroy(&role->types);
	}
	kfree(datum);
	return 0;
}