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
#define  BIO_CTRL_DUP 133 
#define  BIO_CTRL_EOF 132 
#define  BIO_CTRL_FLUSH 131 
#define  BIO_CTRL_POP 130 
#define  BIO_CTRL_PUSH 129 
#define  BIO_CTRL_RESET 128 
 int /*<<< orphan*/  BIO_set_retry_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long always_retry_ctrl(BIO *bio, int cmd, long num, void *ptr)
{
    long ret = 1;

    switch (cmd) {
    case BIO_CTRL_FLUSH:
        BIO_set_retry_write(bio);
        /* fall through */
    case BIO_CTRL_EOF:
    case BIO_CTRL_RESET:
    case BIO_CTRL_DUP:
    case BIO_CTRL_PUSH:
    case BIO_CTRL_POP:
    default:
        ret = 0;
        break;
    }
    return ret;
}