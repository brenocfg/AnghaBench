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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {char const* filename; int /*<<< orphan*/  checksum; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 TYPE_1__* current_info ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 

void llvm_gcda_start_file(const char *orig_filename, const char version[4],
		u32 checksum)
{
	current_info->filename = orig_filename;
	memcpy(&current_info->version, version, sizeof(current_info->version));
	current_info->checksum = checksum;
}