#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int init; int num; int shutdown; int /*<<< orphan*/  flags; scalar_t__ ptr; } ;
struct TYPE_8__ {char* param_serv; char* param_addr; int bind_mode; int accept_family; int accepted_mode; int accept_sock; char* cache_accepting_name; char* cache_accepting_serv; char* cache_peer_name; char* cache_peer_serv; int /*<<< orphan*/  addr_iter; int /*<<< orphan*/  state; TYPE_2__* bio_chain; int /*<<< orphan*/ * addr_first; } ;
typedef  TYPE_1__ BIO_ACCEPT ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPT_S_ACCEPT ; 
 int /*<<< orphan*/  ACPT_S_BEFORE ; 
#define  AF_INET 144 
#define  AF_INET6 143 
 int /*<<< orphan*/  BIO_ADDRINFO_family (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_free (int /*<<< orphan*/ *) ; 
#define  BIO_CTRL_DUP 142 
#define  BIO_CTRL_FLUSH 141 
#define  BIO_CTRL_GET_CLOSE 140 
#define  BIO_CTRL_PENDING 139 
#define  BIO_CTRL_RESET 138 
#define  BIO_CTRL_SET_CLOSE 137 
#define  BIO_CTRL_WPENDING 136 
#define  BIO_C_DO_STATE_MACHINE 135 
#define  BIO_C_GET_ACCEPT 134 
#define  BIO_C_GET_BIND_MODE 133 
#define  BIO_C_GET_FD 132 
#define  BIO_C_SET_ACCEPT 131 
#define  BIO_C_SET_BIND_MODE 130 
#define  BIO_C_SET_FD 129 
#define  BIO_C_SET_NBIO 128 
 long BIO_FAMILY_IPV4 ; 
 long BIO_FAMILY_IPV6 ; 
 int /*<<< orphan*/  BIO_PARSE_PRIO_SERV ; 
 int BIO_SOCK_NONBLOCK ; 
 int /*<<< orphan*/  BIO_free (TYPE_2__*) ; 
 long BIO_parse_hostserv (void*,char**,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (void*) ; 
 int /*<<< orphan*/  acpt_close_socket (TYPE_2__*) ; 
 scalar_t__ acpt_state (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static long acpt_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    int *ip;
    long ret = 1;
    BIO_ACCEPT *data;
    char **pp;

    data = (BIO_ACCEPT *)b->ptr;

    switch (cmd) {
    case BIO_CTRL_RESET:
        ret = 0;
        data->state = ACPT_S_BEFORE;
        acpt_close_socket(b);
        BIO_ADDRINFO_free(data->addr_first);
        data->addr_first = NULL;
        b->flags = 0;
        break;
    case BIO_C_DO_STATE_MACHINE:
        /* use this one to start the connection */
        ret = (long)acpt_state(b, data);
        break;
    case BIO_C_SET_ACCEPT:
        if (ptr != NULL) {
            if (num == 0) {
                char *hold_serv = data->param_serv;
                /* We affect the hostname regardless.  However, the input
                 * string might contain a host:service spec, so we must
                 * parse it, which might or might not affect the service
                 */
                OPENSSL_free(data->param_addr);
                data->param_addr = NULL;
                ret = BIO_parse_hostserv(ptr,
                                         &data->param_addr,
                                         &data->param_serv,
                                         BIO_PARSE_PRIO_SERV);
                if (hold_serv != data->param_serv)
                    OPENSSL_free(hold_serv);
                b->init = 1;
            } else if (num == 1) {
                OPENSSL_free(data->param_serv);
                data->param_serv = OPENSSL_strdup(ptr);
                b->init = 1;
            } else if (num == 2) {
                data->bind_mode |= BIO_SOCK_NONBLOCK;
            } else if (num == 3) {
                BIO_free(data->bio_chain);
                data->bio_chain = (BIO *)ptr;
            } else if (num == 4) {
                data->accept_family = *(int *)ptr;
            }
        } else {
            if (num == 2) {
                data->bind_mode &= ~BIO_SOCK_NONBLOCK;
            }
        }
        break;
    case BIO_C_SET_NBIO:
        if (num != 0)
            data->accepted_mode |= BIO_SOCK_NONBLOCK;
        else
            data->accepted_mode &= ~BIO_SOCK_NONBLOCK;
        break;
    case BIO_C_SET_FD:
        b->num = *((int *)ptr);
        data->accept_sock = b->num;
        data->state = ACPT_S_ACCEPT;
        b->shutdown = (int)num;
        b->init = 1;
        break;
    case BIO_C_GET_FD:
        if (b->init) {
            ip = (int *)ptr;
            if (ip != NULL)
                *ip = data->accept_sock;
            ret = data->accept_sock;
        } else
            ret = -1;
        break;
    case BIO_C_GET_ACCEPT:
        if (b->init) {
            if (num == 0 && ptr != NULL) {
                pp = (char **)ptr;
                *pp = data->cache_accepting_name;
            } else if (num == 1 && ptr != NULL) {
                pp = (char **)ptr;
                *pp = data->cache_accepting_serv;
            } else if (num == 2 && ptr != NULL) {
                pp = (char **)ptr;
                *pp = data->cache_peer_name;
            } else if (num == 3 && ptr != NULL) {
                pp = (char **)ptr;
                *pp = data->cache_peer_serv;
            } else if (num == 4) {
                switch (BIO_ADDRINFO_family(data->addr_iter)) {
#ifdef AF_INET6
                case AF_INET6:
                    ret = BIO_FAMILY_IPV6;
                    break;
#endif
                case AF_INET:
                    ret = BIO_FAMILY_IPV4;
                    break;
                case 0:
                    ret = data->accept_family;
                    break;
                default:
                    ret = -1;
                    break;
                }
            } else
                ret = -1;
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
    case BIO_CTRL_FLUSH:
        break;
    case BIO_C_SET_BIND_MODE:
        data->bind_mode = (int)num;
        break;
    case BIO_C_GET_BIND_MODE:
        ret = (long)data->bind_mode;
        break;
    case BIO_CTRL_DUP:
        break;

    default:
        ret = 0;
        break;
    }
    return ret;
}