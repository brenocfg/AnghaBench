#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tls12_crypto_info_aes_gcm_128 {int dummy; } ;
struct TYPE_8__ {int num; int shutdown; int init; void* ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
#define  BIO_CTRL_CLEAR_KTLS_TX_CTRL_MSG 138 
#define  BIO_CTRL_DUP 137 
#define  BIO_CTRL_FLUSH 136 
#define  BIO_CTRL_GET_CLOSE 135 
#define  BIO_CTRL_GET_KTLS_RECV 134 
#define  BIO_CTRL_GET_KTLS_SEND 133 
#define  BIO_CTRL_SET_CLOSE 132 
#define  BIO_CTRL_SET_KTLS 131 
#define  BIO_CTRL_SET_KTLS_TX_SEND_CTRL_MSG 130 
#define  BIO_C_GET_FD 129 
#define  BIO_C_SET_FD 128 
 int /*<<< orphan*/  BIO_clear_ktls_ctrl_msg_flag (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_set_ktls_ctrl_msg_flag (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_set_ktls_flag (TYPE_1__*,long) ; 
 long BIO_should_ktls_flag (TYPE_1__*,int) ; 
 long ktls_start (long,struct tls12_crypto_info_aes_gcm_128*,int,long) ; 
 int /*<<< orphan*/  sock_free (TYPE_1__*) ; 

__attribute__((used)) static long sock_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 1;
    int *ip;
# ifndef OPENSSL_NO_KTLS
    struct tls12_crypto_info_aes_gcm_128 *crypto_info;
# endif

    switch (cmd) {
    case BIO_C_SET_FD:
        sock_free(b);
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
    case BIO_CTRL_DUP:
    case BIO_CTRL_FLUSH:
        ret = 1;
        break;
# ifndef OPENSSL_NO_KTLS
    case BIO_CTRL_SET_KTLS:
        crypto_info = (struct tls12_crypto_info_aes_gcm_128 *)ptr;
        ret = ktls_start(b->num, crypto_info, sizeof(*crypto_info), num);
        if (ret)
            BIO_set_ktls_flag(b, num);
        break;
    case BIO_CTRL_GET_KTLS_SEND:
        return BIO_should_ktls_flag(b, 1);
    case BIO_CTRL_GET_KTLS_RECV:
        return BIO_should_ktls_flag(b, 0);
    case BIO_CTRL_SET_KTLS_TX_SEND_CTRL_MSG:
        BIO_set_ktls_ctrl_msg_flag(b);
        b->ptr = (void *)num;
        ret = 0;
        break;
    case BIO_CTRL_CLEAR_KTLS_TX_CTRL_MSG:
        BIO_clear_ktls_ctrl_msg_flag(b);
        ret = 0;
        break;
# endif
    default:
        ret = 0;
        break;
    }
    return ret;
}