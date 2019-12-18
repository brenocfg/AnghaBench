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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  procfile ;
typedef  int /*<<< orphan*/  DICTIONARY ;

/* Variables and functions */
 int /*<<< orphan*/  DICTIONARY_FLAG_SINGLE_THREADED ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  collect_first_zram_metrics ; 
 int /*<<< orphan*/  collect_zram_metrics ; 
 int /*<<< orphan*/ * dictionary_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_get_all_name_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int init_devices (int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  procfile_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * procfile_open (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int try_get_zram_major_number (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_sys_block_zram(int update_every, usec_t dt) {
    (void)dt;
    static procfile *ff = NULL;
    static DICTIONARY *devices = NULL;
    static int initialized = 0;
    static int device_count = 0;
    int zram_id = -1;
    if (unlikely(!initialized))
    {
        initialized = 1;
        ff = procfile_open("/proc/devices", " \t:", PROCFILE_FLAG_DEFAULT);
        if (ff == NULL)
        {
            error("Cannot read /proc/devices");
            return 1;
        }
        ff = procfile_readall(ff);
        if (!ff)
            return 1;
        zram_id = try_get_zram_major_number(ff);
        if (zram_id == -1)
        {
            if (ff != NULL)
                procfile_close(ff);
            return 1;
        }
        procfile_close(ff);

        devices = dictionary_create(DICTIONARY_FLAG_SINGLE_THREADED);
        device_count = init_devices(devices, (unsigned int)zram_id, update_every);
        if (device_count < 1)
            return 1;
        dictionary_get_all_name_value(devices, collect_first_zram_metrics, devices);
    }
    else
    {
        if (unlikely(device_count < 1))
            return 1;
        dictionary_get_all_name_value(devices, collect_zram_metrics, devices);
    }
    return 0;
}