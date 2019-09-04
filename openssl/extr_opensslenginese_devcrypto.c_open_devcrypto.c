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
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ cfd ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static int open_devcrypto(void)
{
    if (cfd >= 0)
        return 1;

    if ((cfd = open("/dev/crypto", O_RDWR, 0)) < 0) {
#ifndef ENGINE_DEVCRYPTO_DEBUG
        if (errno != ENOENT)
#endif
            fprintf(stderr, "Could not open /dev/crypto: %s\n", strerror(errno));
        return 0;
    }

    return 1;
}