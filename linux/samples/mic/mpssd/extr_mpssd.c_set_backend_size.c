#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int backend_size; int /*<<< orphan*/  backend_file; int /*<<< orphan*/  backend; } ;
struct mic_info {TYPE_2__ mic_virtblk; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int capacity; } ;
struct TYPE_6__ {TYPE_1__ blk_config; } ;

/* Variables and functions */
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int htole64 (int) ; 
 int lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsslog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ virtblk_dev_page ; 

__attribute__((used)) static bool
set_backend_size(struct mic_info *mic)
{
	mic->mic_virtblk.backend_size = lseek(mic->mic_virtblk.backend, 0,
		SEEK_END);
	if (mic->mic_virtblk.backend_size < 0) {
		mpsslog("%s: can't seek: %s\n",
			mic->name, mic->mic_virtblk.backend_file);
		return false;
	}
	virtblk_dev_page.blk_config.capacity =
		mic->mic_virtblk.backend_size / SECTOR_SIZE;
	if ((mic->mic_virtblk.backend_size % SECTOR_SIZE) != 0)
		virtblk_dev_page.blk_config.capacity++;

	virtblk_dev_page.blk_config.capacity =
		htole64(virtblk_dev_page.blk_config.capacity);

	return true;
}