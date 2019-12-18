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
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  int /*<<< orphan*/  BN_ULLONG ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int,int) ; 

char *BN_options(void)
{
    static int init = 0;
    static char data[16];

    if (!init) {
        init++;
#ifdef BN_LLONG
        BIO_snprintf(data, sizeof(data), "bn(%zu,%zu)",
                     sizeof(BN_ULLONG) * 8, sizeof(BN_ULONG) * 8);
#else
        BIO_snprintf(data, sizeof(data), "bn(%zu,%zu)",
                     sizeof(BN_ULONG) * 8, sizeof(BN_ULONG) * 8);
#endif
    }
    return data;
}