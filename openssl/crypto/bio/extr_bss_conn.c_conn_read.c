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
struct TYPE_9__ {int /*<<< orphan*/  num; scalar_t__ ptr; } ;
struct TYPE_8__ {scalar_t__ state; } ;
typedef  TYPE_1__ BIO_CONNECT ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 scalar_t__ BIO_CONN_S_OK ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_set_retry_read (TYPE_2__*) ; 
 scalar_t__ BIO_sock_should_retry (int) ; 
 int /*<<< orphan*/  clear_socket_error () ; 
 int conn_state (TYPE_2__*,TYPE_1__*) ; 
 int readsocket (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int conn_read(BIO *b, char *out, int outl)
{
    int ret = 0;
    BIO_CONNECT *data;

    data = (BIO_CONNECT *)b->ptr;
    if (data->state != BIO_CONN_S_OK) {
        ret = conn_state(b, data);
        if (ret <= 0)
            return ret;
    }

    if (out != NULL) {
        clear_socket_error();
        ret = readsocket(b->num, out, outl);
        BIO_clear_retry_flags(b);
        if (ret <= 0) {
            if (BIO_sock_should_retry(ret))
                BIO_set_retry_read(b);
        }
    }
    return ret;
}