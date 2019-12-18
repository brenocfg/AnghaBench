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
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 int /*<<< orphan*/  PROCFILE_FLAG_NO_ERROR_ON_FILE_IO ; 
 int /*<<< orphan*/  procfile_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * procfile_open (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 

int check_proc_1_io() {
    int ret = 0;

    procfile *ff = procfile_open("/proc/1/io", NULL, PROCFILE_FLAG_NO_ERROR_ON_FILE_IO);
    if(!ff) goto cleanup;

    ff = procfile_readall(ff);
    if(!ff) goto cleanup;

    ret = 1;

cleanup:
    procfile_close(ff);
    return ret;
}