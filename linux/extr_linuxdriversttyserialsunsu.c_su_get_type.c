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
struct device_node {int dummy; } ;
typedef  enum su_type { ____Placeholder_su_type } su_type ;

/* Variables and functions */
 int SU_PORT_KBD ; 
 int SU_PORT_MS ; 
 int SU_PORT_PORT ; 
 struct device_node* of_find_node_by_path (char const*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static enum su_type su_get_type(struct device_node *dp)
{
	struct device_node *ap = of_find_node_by_path("/aliases");
	enum su_type rc = SU_PORT_PORT;

	if (ap) {
		const char *keyb = of_get_property(ap, "keyboard", NULL);
		const char *ms = of_get_property(ap, "mouse", NULL);
		struct device_node *match;

		if (keyb) {
			match = of_find_node_by_path(keyb);

			/*
			 * The pointer is used as an identifier not
			 * as a pointer, we can drop the refcount on
			 * the of__node immediately after getting it.
			 */
			of_node_put(match);

			if (dp == match) {
				rc = SU_PORT_KBD;
				goto out;
			}
		}
		if (ms) {
			match = of_find_node_by_path(ms);

			of_node_put(match);

			if (dp == match) {
				rc = SU_PORT_MS;
				goto out;
			}
		}
	}

out:
	of_node_put(ap);
	return rc;
}