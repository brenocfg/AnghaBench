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
 int BIO_sock_non_fatal_error (int) ; 
 int get_last_socket_error () ; 

int BIO_sock_should_retry(int i)
{
    int err;

    if ((i == 0) || (i == -1)) {
        err = get_last_socket_error();

        return BIO_sock_non_fatal_error(err);
    }
    return 0;
}