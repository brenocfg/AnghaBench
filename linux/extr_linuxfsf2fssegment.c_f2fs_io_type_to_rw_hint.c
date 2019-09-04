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
struct f2fs_sb_info {int dummy; } ;
typedef  enum temp_type { ____Placeholder_temp_type } temp_type ;
typedef  enum rw_hint { ____Placeholder_rw_hint } rw_hint ;
typedef  enum page_type { ____Placeholder_page_type } page_type ;
struct TYPE_2__ {scalar_t__ whint_mode; } ;

/* Variables and functions */
 int COLD ; 
 int DATA ; 
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int HOT ; 
 int META ; 
 int NODE ; 
 int WARM ; 
 scalar_t__ WHINT_MODE_FS ; 
 scalar_t__ WHINT_MODE_USER ; 
 int WRITE_LIFE_EXTREME ; 
 int WRITE_LIFE_LONG ; 
 int WRITE_LIFE_MEDIUM ; 
 int WRITE_LIFE_NONE ; 
 int WRITE_LIFE_NOT_SET ; 
 int WRITE_LIFE_SHORT ; 

enum rw_hint f2fs_io_type_to_rw_hint(struct f2fs_sb_info *sbi,
				enum page_type type, enum temp_type temp)
{
	if (F2FS_OPTION(sbi).whint_mode == WHINT_MODE_USER) {
		if (type == DATA) {
			if (temp == WARM)
				return WRITE_LIFE_NOT_SET;
			else if (temp == HOT)
				return WRITE_LIFE_SHORT;
			else if (temp == COLD)
				return WRITE_LIFE_EXTREME;
		} else {
			return WRITE_LIFE_NOT_SET;
		}
	} else if (F2FS_OPTION(sbi).whint_mode == WHINT_MODE_FS) {
		if (type == DATA) {
			if (temp == WARM)
				return WRITE_LIFE_LONG;
			else if (temp == HOT)
				return WRITE_LIFE_SHORT;
			else if (temp == COLD)
				return WRITE_LIFE_EXTREME;
		} else if (type == NODE) {
			if (temp == WARM || temp == HOT)
				return WRITE_LIFE_NOT_SET;
			else if (temp == COLD)
				return WRITE_LIFE_NONE;
		} else if (type == META) {
			return WRITE_LIFE_MEDIUM;
		}
	}
	return WRITE_LIFE_NOT_SET;
}