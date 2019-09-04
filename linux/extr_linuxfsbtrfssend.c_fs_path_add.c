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
struct fs_path {int dummy; } ;

/* Variables and functions */
 int fs_path_prepare_for_add (struct fs_path*,int,char**) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int fs_path_add(struct fs_path *p, const char *name, int name_len)
{
	int ret;
	char *prepared;

	ret = fs_path_prepare_for_add(p, name_len, &prepared);
	if (ret < 0)
		goto out;
	memcpy(prepared, name, name_len);

out:
	return ret;
}