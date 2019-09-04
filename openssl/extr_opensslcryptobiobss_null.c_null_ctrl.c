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
#define  BIO_CTRL_DUP 138 
#define  BIO_CTRL_EOF 137 
#define  BIO_CTRL_FLUSH 136 
#define  BIO_CTRL_GET 135 
#define  BIO_CTRL_GET_CLOSE 134 
#define  BIO_CTRL_INFO 133 
#define  BIO_CTRL_PENDING 132 
#define  BIO_CTRL_RESET 131 
#define  BIO_CTRL_SET 130 
#define  BIO_CTRL_SET_CLOSE 129 
#define  BIO_CTRL_WPENDING 128 

__attribute__((used)) static long null_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 1;

    switch (cmd) {
    case BIO_CTRL_RESET:
    case BIO_CTRL_EOF:
    case BIO_CTRL_SET:
    case BIO_CTRL_SET_CLOSE:
    case BIO_CTRL_FLUSH:
    case BIO_CTRL_DUP:
        ret = 1;
        break;
    case BIO_CTRL_GET_CLOSE:
    case BIO_CTRL_INFO:
    case BIO_CTRL_GET:
    case BIO_CTRL_PENDING:
    case BIO_CTRL_WPENDING:
    default:
        ret = 0;
        break;
    }
    return ret;
}