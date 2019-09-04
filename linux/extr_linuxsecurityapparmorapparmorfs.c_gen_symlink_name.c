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
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *gen_symlink_name(int depth, const char *dirname, const char *fname)
{
	char *buffer, *s;
	int error;
	int size = depth * 6 + strlen(dirname) + strlen(fname) + 11;

	s = buffer = kmalloc(size, GFP_KERNEL);
	if (!buffer)
		return ERR_PTR(-ENOMEM);

	for (; depth > 0; depth--) {
		strcpy(s, "../../");
		s += 6;
		size -= 6;
	}

	error = snprintf(s, size, "raw_data/%s/%s", dirname, fname);
	if (error >= size || error < 0) {
		kfree(buffer);
		return ERR_PTR(-ENAMETOOLONG);
	}

	return buffer;
}