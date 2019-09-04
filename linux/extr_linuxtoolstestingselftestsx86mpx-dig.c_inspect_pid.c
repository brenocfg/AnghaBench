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
typedef  int /*<<< orphan*/  bounds_dir_buf ;

/* Variables and functions */
 long MPX_BOUNDS_TABLE_SIZE_BYTES ; 
 int /*<<< orphan*/  dprintf4 (char*,...) ; 
 char* fill_bounds_dir_buf_other (long,int,char*) ; 
 char* fill_bounds_dir_buf_self (long,int,char*) ; 
 int getpid () ; 
 int /*<<< orphan*/  mpx_dig_abort () ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int search_bd_buf (char*,int,long,int*) ; 

int inspect_pid(int pid)
{
	static int dig_nr;
	long offset_inside_bounds_dir;
	char bounds_dir_buf[sizeof(unsigned long) * (1UL << 15)];
	char *dig_bounds_dir_ptr;
	int total_entries = 0;
	int nr_populated_bdes = 0;
	int inspect_self;

	if (getpid() == pid) {
		dprintf4("inspecting self\n");
		inspect_self = 1;
	} else {
		dprintf4("inspecting pid %d\n", pid);
		mpx_dig_abort();
	}

	for (offset_inside_bounds_dir = 0;
	     offset_inside_bounds_dir < MPX_BOUNDS_TABLE_SIZE_BYTES;
	     offset_inside_bounds_dir += sizeof(bounds_dir_buf)) {
		static int bufs_skipped;
		int this_entries;

		if (inspect_self) {
			dig_bounds_dir_ptr =
				fill_bounds_dir_buf_self(offset_inside_bounds_dir,
							 sizeof(bounds_dir_buf),
							 &bounds_dir_buf[0]);
		} else {
			dig_bounds_dir_ptr =
				fill_bounds_dir_buf_other(offset_inside_bounds_dir,
							  sizeof(bounds_dir_buf),
							  &bounds_dir_buf[0]);
		}
		if (!dig_bounds_dir_ptr) {
			bufs_skipped++;
			continue;
		}
		this_entries = search_bd_buf(dig_bounds_dir_ptr,
					sizeof(bounds_dir_buf),
					offset_inside_bounds_dir,
					&nr_populated_bdes);
		total_entries += this_entries;
	}
	printf("mpx dig (%3d) complete, SUCCESS (%8d / %4d)\n", ++dig_nr,
			total_entries, nr_populated_bdes);
	return total_entries + nr_populated_bdes;
}