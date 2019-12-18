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
struct fs_path {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int fs_path_prepare_for_add (struct fs_path*,scalar_t__,char**) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int fs_path_add_path(struct fs_path *p, struct fs_path *p2)
{
	int ret;
	char *prepared;

	ret = fs_path_prepare_for_add(p, p2->end - p2->start, &prepared);
	if (ret < 0)
		goto out;
	memcpy(prepared, p2->start, p2->end - p2->start);

out:
	return ret;
}