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
struct iso_directory_record {char* name; int* name_len; } ;
struct inode {int dummy; } ;

/* Variables and functions */

int isofs_name_translate(struct iso_directory_record *de, char *new, struct inode *inode)
{
	char * old = de->name;
	int len = de->name_len[0];
	int i;

	for (i = 0; i < len; i++) {
		unsigned char c = old[i];
		if (!c)
			break;

		if (c >= 'A' && c <= 'Z')
			c |= 0x20;	/* lower case */

		/* Drop trailing '.;1' (ISO 9660:1988 7.5.1 requires period) */
		if (c == '.' && i == len - 3 && old[i + 1] == ';' && old[i + 2] == '1')
			break;

		/* Drop trailing ';1' */
		if (c == ';' && i == len - 2 && old[i + 1] == '1')
			break;

		/* Convert remaining ';' to '.' */
		/* Also '/' to '.' (broken Acorn-generated ISO9660 images) */
		if (c == ';' || c == '/')
			c = '.';

		new[i] = c;
	}
	return i;
}