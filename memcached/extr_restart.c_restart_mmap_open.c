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

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  S_IRWXU ; 
 long _find_pagesize () ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ftruncate (int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  memory_file ; 
 void* mmap (int /*<<< orphan*/ *,size_t const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mmap_base ; 
 int /*<<< orphan*/  mmap_fd ; 
 int /*<<< orphan*/  open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ restart_check (char const*) ; 
 size_t slabmem_limit ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strdup (char const*) ; 

bool restart_mmap_open(const size_t limit, const char *file, void **mem_base) {
    bool reuse_mmap = true;

    long pagesize = _find_pagesize();
    memory_file = strdup(file);
    mmap_fd = open(file, O_RDWR|O_CREAT, S_IRWXU);
    if (ftruncate(mmap_fd, limit) != 0) {
        perror("ftruncate failed");
        abort();
    }
    /* Allocate everything in a big chunk with malloc */
    if (limit % pagesize) {
        // This is a sanity check; shouldn't ever be possible since we
        // increase memory by whole megabytes.
        fprintf(stderr, "[restart] memory limit not divisible evenly by pagesize (please report bug)\n");
        abort();
    }
    mmap_base = mmap(NULL, limit, PROT_READ|PROT_WRITE, MAP_SHARED, mmap_fd, 0);
    if (mmap_base == MAP_FAILED) {
        perror("failed to mmap, aborting");
        abort();
    }
    // Set the limit before calling check_mmap, so we can find the meta page..
    slabmem_limit = limit;
    if (restart_check(file) != 0) {
        reuse_mmap = false;
    }
    *mem_base = mmap_base;

    return reuse_mmap;
}