#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rec_len; } ;
typedef  TYPE_1__ ext2_dirent ;

/* Variables and functions */
 int ext2_rec_len_from_disk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ext2_dirent *ext2_next_entry(ext2_dirent *p)
{
	return (ext2_dirent *)((char *)p +
			ext2_rec_len_from_disk(p->rec_len));
}