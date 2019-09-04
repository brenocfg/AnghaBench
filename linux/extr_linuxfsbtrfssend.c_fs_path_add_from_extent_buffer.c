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
struct extent_buffer {int dummy; } ;

/* Variables and functions */
 int fs_path_prepare_for_add (struct fs_path*,int,char**) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,char*,unsigned long,int) ; 

__attribute__((used)) static int fs_path_add_from_extent_buffer(struct fs_path *p,
					  struct extent_buffer *eb,
					  unsigned long off, int len)
{
	int ret;
	char *prepared;

	ret = fs_path_prepare_for_add(p, len, &prepared);
	if (ret < 0)
		goto out;

	read_extent_buffer(eb, prepared, off, len);

out:
	return ret;
}