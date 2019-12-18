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
struct dirent {char* d_name; unsigned long long d_ino; unsigned int d_type; unsigned long long d_off; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

char *read_dir(void *stream, unsigned long long *pos_out,
	       unsigned long long *ino_out, int *len_out,
	       unsigned int *type_out)
{
	DIR *dir = stream;
	struct dirent *ent;

	ent = readdir(dir);
	if (ent == NULL)
		return NULL;
	*len_out = strlen(ent->d_name);
	*ino_out = ent->d_ino;
	*type_out = ent->d_type;
	*pos_out = ent->d_off;
	return ent->d_name;
}