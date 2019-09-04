#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  _errno; int /*<<< orphan*/  peer; scalar_t__ connected; } ;
typedef  TYPE_1__ bio_dgram_data ;
struct TYPE_7__ {int /*<<< orphan*/  num; scalar_t__ ptr; } ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDR_sockaddr (int /*<<< orphan*/ *) ; 
 int BIO_ADDR_sockaddr_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_2__*) ; 
 scalar_t__ BIO_dgram_should_retry (int) ; 
 int /*<<< orphan*/  BIO_set_retry_write (TYPE_2__*) ; 
 int /*<<< orphan*/  clear_socket_error () ; 
 int /*<<< orphan*/  get_last_socket_error () ; 
 int sendto (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int writesocket (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int dgram_write(BIO *b, const char *in, int inl)
{
    int ret;
    bio_dgram_data *data = (bio_dgram_data *)b->ptr;
    clear_socket_error();

    if (data->connected)
        ret = writesocket(b->num, in, inl);
    else {
        int peerlen = BIO_ADDR_sockaddr_size(&data->peer);

        ret = sendto(b->num, in, inl, 0,
                     BIO_ADDR_sockaddr(&data->peer), peerlen);
    }

    BIO_clear_retry_flags(b);
    if (ret <= 0) {
        if (BIO_dgram_should_retry(ret)) {
            BIO_set_retry_write(b);
            data->_errno = get_last_socket_error();
        }
    }
    return ret;
}