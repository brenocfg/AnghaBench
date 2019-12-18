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
 int cfd ; 
 int close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int close_devcrypto(void)
{
    int ret;

    if (cfd < 0)
        return 1;
    ret = close(cfd);
    cfd = -1;
    if (ret != 0) {
        fprintf(stderr, "Error closing /dev/crypto: %s\n", strerror(errno));
        return 0;
    }
    return 1;
}