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
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 scalar_t__ keep_cpuidle_fds_open ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int read_one_state(char *buf, const char *filename, int *fd) {
    ssize_t ret = read(*fd, buf, 50);

    if(unlikely(ret <= 0)) {
        // cannot read that file
        error("Cannot read file '%s'", filename);
        close(*fd);
        *fd = -1;
        return 0;
    }
    else {
        // successful read

        // terminate the buffer
        buf[ret - 1] = '\0';

        if(unlikely(keep_cpuidle_fds_open != CONFIG_BOOLEAN_YES)) {
            close(*fd);
            *fd = -1;
        }
        else if(lseek(*fd, 0, SEEK_SET) == -1) {
            error("Cannot seek in file '%s'", filename);
            close(*fd);
            *fd = -1;
        }
    }

    return 1;
}