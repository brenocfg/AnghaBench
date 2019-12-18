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
struct TYPE_4__ {int num; int shutdown; int init; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
#define  BIO_CTRL_DUP 139 
#define  BIO_CTRL_FLUSH 138 
#define  BIO_CTRL_GET_CLOSE 137 
#define  BIO_CTRL_INFO 136 
#define  BIO_CTRL_PENDING 135 
#define  BIO_CTRL_RESET 134 
#define  BIO_CTRL_SET_CLOSE 133 
#define  BIO_CTRL_WPENDING 132 
#define  BIO_C_FILE_SEEK 131 
#define  BIO_C_FILE_TELL 130 
#define  BIO_C_GET_FD 129 
#define  BIO_C_SET_FD 128 
 scalar_t__ UP_lseek (int,long,int) ; 
 int /*<<< orphan*/  fd_free (TYPE_1__*) ; 

__attribute__((used)) static long fd_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 1;
    int *ip;

    switch (cmd) {
    case BIO_CTRL_RESET:
        num = 0;
        /* fall thru */
    case BIO_C_FILE_SEEK:
        ret = (long)UP_lseek(b->num, num, 0);
        break;
    case BIO_C_FILE_TELL:
    case BIO_CTRL_INFO:
        ret = (long)UP_lseek(b->num, 0, 1);
        break;
    case BIO_C_SET_FD:
        fd_free(b);
        b->num = *((int *)ptr);
        b->shutdown = (int)num;
        b->init = 1;
        break;
    case BIO_C_GET_FD:
        if (b->init) {
            ip = (int *)ptr;
            if (ip != NULL)
                *ip = b->num;
            ret = b->num;
        } else
            ret = -1;
        break;
    case BIO_CTRL_GET_CLOSE:
        ret = b->shutdown;
        break;
    case BIO_CTRL_SET_CLOSE:
        b->shutdown = (int)num;
        break;
    case BIO_CTRL_PENDING:
    case BIO_CTRL_WPENDING:
        ret = 0;
        break;
    case BIO_CTRL_DUP:
    case BIO_CTRL_FLUSH:
        ret = 1;
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}