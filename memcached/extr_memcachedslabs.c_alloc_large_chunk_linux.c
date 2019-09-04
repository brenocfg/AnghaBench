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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int verbose; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MADV_HUGEPAGE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 int madvise (void*,size_t const,int /*<<< orphan*/ ) ; 
 int posix_memalign (void**,size_t,size_t const) ; 
 TYPE_1__ settings ; 
 int sscanf (char*,char*,size_t*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void * alloc_large_chunk_linux(const size_t limit)
{
    size_t pagesize = 0;
    void *ptr = NULL;
    FILE *fp;
    int ret;

    /* Get the size of huge pages */
    fp = fopen("/proc/meminfo", "r");
    if (fp != NULL) {
        char buf[64];

        while ((fgets(buf, sizeof(buf), fp)))
            if (!strncmp(buf, "Hugepagesize:", 13)) {
                ret = sscanf(buf + 13, "%zu\n", &pagesize);

                /* meminfo huge page size is in KiBs */
                pagesize <<= 10;
            }
        fclose(fp);
    }

    if (!pagesize) {
        fprintf(stderr, "Failed to get supported huge page size\n");
        return NULL;
    }

    if (settings.verbose > 1)
        fprintf(stderr, "huge page size: %zu\n", pagesize);

    /* This works because glibc simply uses mmap when the alignment is
     * above a certain limit. */
    ret = posix_memalign(&ptr, pagesize, limit);
    if (ret != 0) {
        fprintf(stderr, "Failed to get aligned memory chunk: %d\n", ret);
        return NULL;
    }

    ret = madvise(ptr, limit, MADV_HUGEPAGE);
    if (ret < 0) {
        fprintf(stderr, "Failed to set transparent hugepage hint: %d\n", ret);
        free(ptr);
        ptr = NULL;
    }

    return ptr;
}