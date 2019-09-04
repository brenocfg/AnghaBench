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
 int BIO_dgram_non_fatal_error (int) ; 
 int get_last_socket_error () ; 

__attribute__((used)) static int BIO_dgram_should_retry(int i)
{
    int err;

    if ((i == 0) || (i == -1)) {
        err = get_last_socket_error();

# if defined(OPENSSL_SYS_WINDOWS)
        /*
         * If the socket return value (i) is -1 and err is unexpectedly 0 at
         * this point, the error code was overwritten by another system call
         * before this error handling is called.
         */
# endif

        return BIO_dgram_non_fatal_error(err);
    }
    return 0;
}