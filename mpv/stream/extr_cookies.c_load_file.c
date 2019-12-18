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
struct mp_log {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*,...) ; 
 int open (char const*,int) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static char *load_file(struct mp_log *log, const char *filename, int64_t * length)
{
    int fd;
    char *buffer = NULL;

    mp_verbose(log, "Loading cookie file: %s\n", filename);

    fd = open(filename, O_RDONLY | O_CLOEXEC);
    if (fd < 0) {
        mp_verbose(log, "Could not open");
        goto err_out;
    }

    *length = lseek(fd, 0, SEEK_END);

    if (*length < 0) {
        mp_verbose(log, "Could not find EOF");
        goto err_out;
    }

    if (*length > SIZE_MAX - 1) {
        mp_verbose(log, "File too big, could not malloc.");
        goto err_out;
    }

    lseek(fd, 0, SEEK_SET);

    if (!(buffer = malloc(*length + 1))) {
        mp_verbose(log, "Could not malloc.");
        goto err_out;
    }

    if (read(fd, buffer, *length) != *length) {
        mp_verbose(log, "Read is behaving funny.");
        goto err_out;
    }
    close(fd);
    buffer[*length] = 0;

    return buffer;

err_out:
    if (fd != -1) close(fd);
    free(buffer);
    return NULL;
}