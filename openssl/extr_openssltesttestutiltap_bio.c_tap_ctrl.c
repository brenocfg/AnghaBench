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
#define  BIO_CTRL_RESET 128 
 long BIO_ctrl (int /*<<< orphan*/ *,int,long,void*) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long tap_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    BIO *next = BIO_next(b);

    switch (cmd) {
    case BIO_CTRL_RESET:
        BIO_set_data(b, NULL);
        break;

    default:
        break;
    }
    return BIO_ctrl(next, cmd, num, ptr);
}