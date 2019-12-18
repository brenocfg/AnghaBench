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
struct fs {int found; int /*<<< orphan*/  path; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* getenv (char*) ; 
 int /*<<< orphan*/  mem_toupper (char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool fs__env_override(struct fs *fs)
{
	char *override_path;
	size_t name_len = strlen(fs->name);
	/* name + "_PATH" + '\0' */
	char upper_name[name_len + 5 + 1];
	memcpy(upper_name, fs->name, name_len);
	mem_toupper(upper_name, name_len);
	strcpy(&upper_name[name_len], "_PATH");

	override_path = getenv(upper_name);
	if (!override_path)
		return false;

	fs->found = true;
	strncpy(fs->path, override_path, sizeof(fs->path));
	return true;
}