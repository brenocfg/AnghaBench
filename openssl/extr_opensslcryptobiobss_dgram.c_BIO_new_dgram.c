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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_datagram () ; 
 int /*<<< orphan*/  BIO_set_fd (int /*<<< orphan*/ *,int,int) ; 

BIO *BIO_new_dgram(int fd, int close_flag)
{
    BIO *ret;

    ret = BIO_new(BIO_s_datagram());
    if (ret == NULL)
        return NULL;
    BIO_set_fd(ret, fd, close_flag);
    return ret;
}