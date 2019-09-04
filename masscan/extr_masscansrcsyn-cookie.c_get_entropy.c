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
typedef  int /*<<< orphan*/  urand ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fopen_s (int /*<<< orphan*/ **,char*,char*) ; 
 int fread (int*,int,int,int /*<<< orphan*/ *) ; 
 int pixie_nanotime () ; 
 int time (int /*<<< orphan*/ ) ; 

uint64_t
get_entropy(void)
{
    uint64_t entropy[2] = {0,0};
    unsigned i;

    /*
     * Gather some random bits
     */
    for (i=0; i<64; i++) {
        FILE *fp;
        entropy[0] += pixie_nanotime();
#if defined(_MSC_VER)
        entropy[0] ^= __rdtsc();
#endif
        time(0);
        fopen_s(&fp, "/", "r");
        entropy[1] <<= 1;
        entropy[1] |= entropy[0]>>63;
        entropy[0] <<= 1;
    }

    entropy[0] ^= time(0);

#if defined(__linux__)
    {
        FILE *fp;
        int err;

        err = fopen_s(&fp, "/dev/urandom", "r");
        if (err == 0 && fp) {
            int x;
            uint64_t urand = 0;
            x = fread(&urand, 1, sizeof(urand), fp);
            entropy[0] ^= urand;
            entropy[0] ^= x;
            x = fread(&urand, 1, sizeof(urand), fp);
            entropy[1] ^= urand;
            entropy[1] ^= x;
            fclose(fp);
        }
        entropy[0] ^= pixie_nanotime();
    }
#endif

    return entropy[0] ^ entropy[1];
}