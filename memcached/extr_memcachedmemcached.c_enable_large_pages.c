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

__attribute__((used)) static int enable_large_pages(void) {
#if defined(HAVE_GETPAGESIZES) && defined(HAVE_MEMCNTL)
    int ret = -1;
    size_t sizes[32];
    int avail = getpagesizes(sizes, 32);
    if (avail != -1) {
        size_t max = sizes[0];
        struct memcntl_mha arg = {0};
        int ii;

        for (ii = 1; ii < avail; ++ii) {
            if (max < sizes[ii]) {
                max = sizes[ii];
            }
        }

        arg.mha_flags   = 0;
        arg.mha_pagesize = max;
        arg.mha_cmd = MHA_MAPSIZE_BSSBRK;

        if (memcntl(0, 0, MC_HAT_ADVISE, (caddr_t)&arg, 0, 0) == -1) {
            fprintf(stderr, "Failed to set large pages: %s\n",
                    strerror(errno));
            fprintf(stderr, "Will use default page size\n");
        } else {
            ret = 0;
        }
    } else {
        fprintf(stderr, "Failed to get supported pagesizes: %s\n",
                strerror(errno));
        fprintf(stderr, "Will use default page size\n");
    }

    return ret;
#elif defined(__linux__) && defined(MADV_HUGEPAGE)
    /* check if transparent hugepages is compiled into the kernel */
    struct stat st;
    int ret = stat("/sys/kernel/mm/transparent_hugepage/enabled", &st);
    if (ret || !(st.st_mode & S_IFREG)) {
        fprintf(stderr, "Transparent huge pages support not detected.\n");
        fprintf(stderr, "Will use default page size.\n");
        return -1;
    }
    return 0;
#elif defined(__FreeBSD__)
    int spages;
    size_t spagesl = sizeof(spages);

    if (sysctlbyname("vm.pmap.pg_ps_enabled", &spages,
    &spagesl, NULL, 0) != 0) {
        fprintf(stderr, "Could not evaluate the presence of superpages features.");
        return -1;
    }
    if (spages != 1) {
        fprintf(stderr, "Superpages support not detected.\n");
        fprintf(stderr, "Will use default page size.\n");
        return -1;
    }
    return 0;
#else
    return -1;
#endif
}