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
struct c2c_dimension {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct c2c_dimension** dimensions ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct c2c_dimension *get_dimension(const char *name)
{
	unsigned int i;

	for (i = 0; dimensions[i]; i++) {
		struct c2c_dimension *dim = dimensions[i];

		if (!strcmp(dim->name, name))
			return dim;
	};

	return NULL;
}