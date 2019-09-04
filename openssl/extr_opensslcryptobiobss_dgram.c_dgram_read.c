#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  peer ;
struct TYPE_9__ {int /*<<< orphan*/  _errno; int /*<<< orphan*/  connected; scalar_t__ peekmode; } ;
typedef  TYPE_1__ bio_dgram_data ;
struct TYPE_10__ {int /*<<< orphan*/  num; scalar_t__ ptr; } ;
typedef  int /*<<< orphan*/  BIO_ADDR ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDR_sockaddr_noconst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_CTRL_DGRAM_SET_PEER ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_ctrl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_dgram_should_retry (int) ; 
 int /*<<< orphan*/  BIO_set_retry_read (TYPE_2__*) ; 
 int MSG_PEEK ; 
 int /*<<< orphan*/  clear_socket_error () ; 
 int /*<<< orphan*/  dgram_adjust_rcv_timeout (TYPE_2__*) ; 
 int /*<<< orphan*/  dgram_reset_rcv_timeout (TYPE_2__*) ; 
 int /*<<< orphan*/  get_last_socket_error () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int recvfrom (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int dgram_read(BIO *b, char *out, int outl)
{
    int ret = 0;
    bio_dgram_data *data = (bio_dgram_data *)b->ptr;
    int flags = 0;

    BIO_ADDR peer;
    socklen_t len = sizeof(peer);

    if (out != NULL) {
        clear_socket_error();
        memset(&peer, 0, sizeof(peer));
        dgram_adjust_rcv_timeout(b);
        if (data->peekmode)
            flags = MSG_PEEK;
        ret = recvfrom(b->num, out, outl, flags,
                       BIO_ADDR_sockaddr_noconst(&peer), &len);

        if (!data->connected && ret >= 0)
            BIO_ctrl(b, BIO_CTRL_DGRAM_SET_PEER, 0, &peer);

        BIO_clear_retry_flags(b);
        if (ret < 0) {
            if (BIO_dgram_should_retry(ret)) {
                BIO_set_retry_read(b);
                data->_errno = get_last_socket_error();
            }
        }

        dgram_reset_rcv_timeout(b);
    }
    return ret;
}