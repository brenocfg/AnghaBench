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
struct TYPE_4__ {int num_write; int /*<<< orphan*/  init; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_C_NWRITE ; 
 int /*<<< orphan*/  BIO_F_BIO_NWRITE ; 
 int /*<<< orphan*/  BIO_R_UNINITIALIZED ; 
 int BIO_ctrl (TYPE_1__*,int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int BIO_nwrite(BIO *bio, char **buf, int num)
{
    int ret;

    if (!bio->init) {
        BIOerr(BIO_F_BIO_NWRITE, BIO_R_UNINITIALIZED);
        return -2;
    }

    ret = BIO_ctrl(bio, BIO_C_NWRITE, num, buf);
    if (ret > 0)
        bio->num_write += ret;
    return ret;
}