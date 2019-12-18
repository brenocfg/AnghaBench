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
typedef  int /*<<< orphan*/  gs_image_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_image_file_init_internal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

void gs_image_file_init(gs_image_file_t *image, const char *file)
{
	gs_image_file_init_internal(image, file, NULL);
}