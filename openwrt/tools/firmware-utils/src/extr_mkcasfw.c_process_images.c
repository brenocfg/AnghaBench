#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct image_desc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_fs_size; int /*<<< orphan*/  max_kernel_size; } ;
struct TYPE_5__ {void* padc; int /*<<< orphan*/  out_size; int /*<<< orphan*/  file_name; } ;

/* Variables and functions */
 void* DEFAULT_PADC ; 
 TYPE_4__* board ; 
 TYPE_1__ fs_image ; 
 int image_stat_file (TYPE_1__*) ; 
 TYPE_1__ kernel_image ; 

int
process_images(void)
{
	struct image_desc *desc;
	uint32_t offs = 0;
	int i;
	int res;

	kernel_image.out_size = board->max_kernel_size;
	kernel_image.padc = DEFAULT_PADC;
	res = image_stat_file(&kernel_image);
	if (res)
		return res;

	if (!fs_image.file_name)
		return 0;

	fs_image.out_size = board->max_fs_size;
	fs_image.padc = DEFAULT_PADC;
	res = image_stat_file(&fs_image);
	if (res)
		return res;

	return 0;
}