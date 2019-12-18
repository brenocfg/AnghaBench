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
struct TYPE_3__ {char* sec; int /*<<< orphan*/  is_attachable; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int MAX_TYPE_NAME_SIZE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 TYPE_1__* section_names ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *libbpf_get_type_names(bool attach_type)
{
	int i, len = ARRAY_SIZE(section_names) * MAX_TYPE_NAME_SIZE;
	char *buf;

	buf = malloc(len);
	if (!buf)
		return NULL;

	buf[0] = '\0';
	/* Forge string buf with all available names */
	for (i = 0; i < ARRAY_SIZE(section_names); i++) {
		if (attach_type && !section_names[i].is_attachable)
			continue;

		if (strlen(buf) + strlen(section_names[i].sec) + 2 > len) {
			free(buf);
			return NULL;
		}
		strcat(buf, " ");
		strcat(buf, section_names[i].sec);
	}

	return buf;
}