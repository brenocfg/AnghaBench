#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  init; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_C_NREAD0 ; 
 int /*<<< orphan*/  BIO_F_BIO_NREAD0 ; 
 int /*<<< orphan*/  BIO_R_UNINITIALIZED ; 
 long BIO_ctrl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long INT_MAX ; 

int BIO_nread0(BIO *bio, char **buf)
{
    long ret;

    if (!bio->init) {
        BIOerr(BIO_F_BIO_NREAD0, BIO_R_UNINITIALIZED);
        return -2;
    }

    ret = BIO_ctrl(bio, BIO_C_NREAD0, 0, buf);
    if (ret > INT_MAX)
        return INT_MAX;
    else
        return (int)ret;
}