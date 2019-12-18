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
struct per_core_single_number_file {int found; int fd; scalar_t__ value; int /*<<< orphan*/  filename; } ;
struct cpu_chart {struct per_core_single_number_file* files; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ keep_per_core_fds_open ; 
 scalar_t__ likely (int) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t read (int,char*,int) ; 
 scalar_t__ str2ll (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int read_per_core_files(struct cpu_chart *all_cpu_charts, size_t len, size_t index) {
    char buf[50 + 1];
    size_t x, files_read = 0, files_nonzero = 0;

    for(x = 0; x < len ; x++) {
        struct per_core_single_number_file *f = &all_cpu_charts[x].files[index];

        f->found = 0;

        if(unlikely(!f->filename))
            continue;

        if(unlikely(f->fd == -1)) {
            f->fd = open(f->filename, O_RDONLY);
            if (unlikely(f->fd == -1)) {
                error("Cannot open file '%s'", f->filename);
                continue;
            }
        }

        ssize_t ret = read(f->fd, buf, 50);
        if(unlikely(ret < 0)) {
            // cannot read that file

            error("Cannot read file '%s'", f->filename);
            close(f->fd);
            f->fd = -1;
            continue;
        }
        else {
            // successful read

            // terminate the buffer
            buf[ret] = '\0';

            if(unlikely(keep_per_core_fds_open != CONFIG_BOOLEAN_YES)) {
                close(f->fd);
                f->fd = -1;
            }
            else if(lseek(f->fd, 0, SEEK_SET) == -1) {
                error("Cannot seek in file '%s'", f->filename);
                close(f->fd);
                f->fd = -1;
            }
        }

        files_read++;
        f->found = 1;

        f->value = str2ll(buf, NULL);
        if(likely(f->value != 0))
            files_nonzero++;
    }

    if(files_read == 0)
        return -1;

    if(files_nonzero == 0)
        return 0;

    return (int)files_nonzero;
}