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
typedef  int /*<<< orphan*/  umode_t ;
struct ocfs2_dir_entry {int /*<<< orphan*/  file_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_umode_to_ftype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ocfs2_set_de_type(struct ocfs2_dir_entry *de,
				    umode_t mode)
{
	de->file_type = fs_umode_to_ftype(mode);
}