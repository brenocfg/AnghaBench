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

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
TrimExtension(char *filename, char *extension)
{
	int			flen;
	int			elen;

	if (extension == NULL)
		return;

	elen = strlen(extension);
	flen = strlen(filename);

	if (flen > elen && strcmp(filename + flen - elen, extension) == 0)
		filename[flen - elen] = '\0';
}