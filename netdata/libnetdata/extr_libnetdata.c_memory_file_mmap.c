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
 int MADV_DONTFORK ; 
 int MADV_SEQUENTIAL ; 
 int MADV_WILLNEED ; 
 void* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ madvise (void*,size_t,int) ; 
 int memory_file_open (char const*,size_t) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmap_accounting (size_t) ; 

__attribute__((used)) static void *memory_file_mmap(const char *filename, size_t size, int flags) {
    // info("memory_file_mmap('%s', %zu", filename, size);
    static int log_madvise = 1;

    int fd = -1;
    if(filename) {
        fd = memory_file_open(filename, size);
        if(fd == -1) return MAP_FAILED;
    }

    void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, flags, fd, 0);
    if (mem != MAP_FAILED) {
#ifdef NETDATA_LOG_ALLOCATIONS
        mmap_accounting(size);
#endif
        int advise = MADV_SEQUENTIAL | MADV_DONTFORK;
        if (flags & MAP_SHARED) advise |= MADV_WILLNEED;

        if (madvise(mem, size, advise) != 0 && log_madvise) {
            error("Cannot advise the kernel about shared memory usage.");
            log_madvise--;
        }
    }

    if(fd != -1)
        close(fd);

    return mem;
}