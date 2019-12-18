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
struct stat {scalar_t__ st_size; } ;
struct TYPE_2__ {void* addr; size_t sz; } ;
struct config {TYPE_1__ mapped; } ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  lwan_status_perror (char*,char const*) ; 
 struct config* malloc (int) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 int open (char const*,int) ; 

__attribute__((used)) static struct config *
config_open_path(const char *path, void **data, size_t *size)
{
    struct config *config;
    struct stat st;
    void *mapped;
    int fd;

    fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd < 0) {
        lwan_status_perror("Could not open configuration file: %s", path);
        return NULL;
    }

    if (fstat(fd, &st) < 0) {
        close(fd);
        return NULL;
    }

    mapped = mmap(NULL, (size_t)st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    if (mapped == MAP_FAILED)
        return NULL;

    config = malloc(sizeof(*config));
    if (!config) {
        munmap(mapped, (size_t)st.st_size);
        return NULL;
    }

    *data = config->mapped.addr = mapped;
    *size = config->mapped.sz = (size_t)st.st_size;

    return config;
}