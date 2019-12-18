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
struct f2fs_io_info {int /*<<< orphan*/  temp; int /*<<< orphan*/  sbi; } ;
struct TYPE_2__ {int active_logs; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLD ; 
 TYPE_1__ F2FS_OPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOT ; 
 scalar_t__ IS_HOT (int) ; 
 scalar_t__ IS_WARM (int) ; 
 int /*<<< orphan*/  WARM ; 
 int __get_segment_type_2 (struct f2fs_io_info*) ; 
 int __get_segment_type_4 (struct f2fs_io_info*) ; 
 int __get_segment_type_6 (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  f2fs_bug_on (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __get_segment_type(struct f2fs_io_info *fio)
{
	int type = 0;

	switch (F2FS_OPTION(fio->sbi).active_logs) {
	case 2:
		type = __get_segment_type_2(fio);
		break;
	case 4:
		type = __get_segment_type_4(fio);
		break;
	case 6:
		type = __get_segment_type_6(fio);
		break;
	default:
		f2fs_bug_on(fio->sbi, true);
	}

	if (IS_HOT(type))
		fio->temp = HOT;
	else if (IS_WARM(type))
		fio->temp = WARM;
	else
		fio->temp = COLD;
	return type;
}