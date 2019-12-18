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
typedef  enum attrib_type { ____Placeholder_attrib_type } attrib_type ;

/* Variables and functions */
 int ATTRIB_COLOR ; 
 int ATTRIB_NORMAL ; 
 int ATTRIB_POSITION ; 
 int ATTRIB_TANGENT ; 
 int ATTRIB_TARGET ; 
 int ATTRIB_TEXCOORD ; 
 scalar_t__ astrcmp_n (char const*,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void get_attrib_type(const char *mapping, enum attrib_type *type,
			    size_t *index)
{
	if (strcmp(mapping, "POSITION") == 0) {
		*type = ATTRIB_POSITION;

	} else if (strcmp(mapping, "NORMAL") == 0) {
		*type = ATTRIB_NORMAL;

	} else if (strcmp(mapping, "TANGENT") == 0) {
		*type = ATTRIB_TANGENT;

	} else if (strcmp(mapping, "COLOR") == 0) {
		*type = ATTRIB_COLOR;

	} else if (astrcmp_n(mapping, "TEXCOORD", 8) == 0) {
		*type = ATTRIB_TEXCOORD;
		*index = (*(mapping + 8)) - '0';
		return;

	} else if (strcmp(mapping, "TARGET") == 0) {
		*type = ATTRIB_TARGET;
	}

	*index = 0;
}