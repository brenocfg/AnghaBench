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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int fopen_s (int /*<<< orphan*/ **,char*,char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

int
PFRING_is_installed(void)
{
#if defined(__linux__)
    FILE *fp;
    int err;
    char line[256];
    int found = 0;

    err = fopen_s(&fp, "/proc/modules", "rb");
    if (err)
        return 0;

    while (fgets(line, sizeof(line), fp)) {
        if (memcmp(line, "pf_ring ", 8) == 0) {
            found = 1;
            LOG(2, "pfring: found 'pf_ring' driver\n");
        }
        if (memcmp(line, "ixgbe ", 6) == 0) {
            LOG(2, "pfring: found 'ixgbe' driver\n");
        }
        if (memcmp(line, "e1000e ", 8) == 0) {
            LOG(2, "pfring: found 'e1000e' driver\n");
        }
    }
    fclose(fp);
    return found;
#else
    return 0;
#endif
}