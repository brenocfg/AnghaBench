#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_rdev; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  procfile ;
struct TYPE_4__ {int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ ZRAM_DEVICE ;
typedef  int /*<<< orphan*/  DIR ;
typedef  int /*<<< orphan*/  DICTIONARY ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictionary_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int /*<<< orphan*/  init_rrd (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 unsigned int major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/ * procfile_open (char*,char*,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int init_devices(DICTIONARY *devices, unsigned int zram_id, int update_every) {
    int count = 0;
    DIR *dir = opendir("/dev");
    struct dirent *de;
    struct stat st;
    char filename[FILENAME_MAX + 1];
    procfile *ff = NULL;
    ZRAM_DEVICE device;

    if (unlikely(!dir))
        return 0;
    while ((de = readdir(dir)))
    {
        snprintfz(filename, FILENAME_MAX, "/dev/%s", de->d_name);
        if (unlikely(stat(filename, &st) != 0))
        {
            error("ZRAM : Unable to stat %s: %s", filename, strerror(errno));
            continue;
        }
        if (major(st.st_rdev) == zram_id)
        {
            info("ZRAM : Found device %s", filename);
            snprintfz(filename, FILENAME_MAX, "/sys/block/%s/mm_stat", de->d_name);
            ff = procfile_open(filename, " \t:", PROCFILE_FLAG_DEFAULT);
            if (ff == NULL)
            {
                error("ZRAM : Failed to open %s: %s", filename, strerror(errno));
                continue;
            }
            device.file = ff;
            init_rrd(de->d_name, &device, update_every);
            dictionary_set(devices, de->d_name, &device, sizeof(ZRAM_DEVICE));
            count++;
        }
    }
    closedir(dir);
    return count;
}