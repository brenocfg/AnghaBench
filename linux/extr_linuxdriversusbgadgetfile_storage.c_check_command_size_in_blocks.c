#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsg_dev {TYPE_1__* curlun; int /*<<< orphan*/  data_size_from_cmnd; } ;
typedef  enum data_direction { ____Placeholder_data_direction } data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  blkbits; } ;

/* Variables and functions */
 int check_command (struct fsg_dev*,int,int,unsigned int,int,char const*) ; 

__attribute__((used)) static int check_command_size_in_blocks(struct fsg_dev *fsg, int cmnd_size,
		enum data_direction data_dir, unsigned int mask,
		int needs_medium, const char *name)
{
	if (fsg->curlun)
		fsg->data_size_from_cmnd <<= fsg->curlun->blkbits;
	return check_command(fsg, cmnd_size, data_dir,
			mask, needs_medium, name);
}