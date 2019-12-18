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
struct font_path_info {int /*<<< orphan*/  path; int /*<<< orphan*/  face_and_style; int /*<<< orphan*/  sizes; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void font_path_info_free(struct font_path_info *info)
{
	bfree(info->sizes);
	bfree(info->face_and_style);
	bfree(info->path);
}