#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int status; scalar_t__ bytes_to_read; int bytes_to_write; int write_buf_len; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  ssl; int /*<<< orphan*/  read_buf_len; int /*<<< orphan*/  read_buf; } ;
typedef  TYPE_1__ PEER ;

/* Variables and functions */
 void* PEER_ERROR ; 
 int PEER_RETRY ; 
 int PEER_SUCCESS ; 
 void* PEER_TEST_FAILURE ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSL_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_int_le (int,scalar_t__) ; 

__attribute__((used)) static void do_app_data_step(PEER *peer)
{
    int ret = 1, write_bytes;

    if (!TEST_int_eq(peer->status, PEER_RETRY)) {
        peer->status = PEER_TEST_FAILURE;
        return;
    }

    /* We read everything available... */
    while (ret > 0 && peer->bytes_to_read) {
        ret = SSL_read(peer->ssl, peer->read_buf, peer->read_buf_len);
        if (ret > 0) {
            if (!TEST_int_le(ret, peer->bytes_to_read)) {
                peer->status = PEER_TEST_FAILURE;
                return;
            }
            peer->bytes_to_read -= ret;
        } else if (ret == 0) {
            peer->status = PEER_ERROR;
            return;
        } else {
            int error = SSL_get_error(peer->ssl, ret);
            if (error != SSL_ERROR_WANT_READ) {
                peer->status = PEER_ERROR;
                return;
            } /* Else continue with write. */
        }
    }

    /* ... but we only write one write-buffer-full of data. */
    write_bytes = peer->bytes_to_write < peer->write_buf_len ? peer->bytes_to_write :
        peer->write_buf_len;
    if (write_bytes) {
        ret = SSL_write(peer->ssl, peer->write_buf, write_bytes);
        if (ret > 0) {
            /* SSL_write will only succeed with a complete write. */
            if (!TEST_int_eq(ret, write_bytes)) {
                peer->status = PEER_TEST_FAILURE;
                return;
            }
            peer->bytes_to_write -= ret;
        } else {
            /*
             * We should perhaps check for SSL_ERROR_WANT_READ/WRITE here
             * but this doesn't yet occur with current app data sizes.
             */
            peer->status = PEER_ERROR;
            return;
        }
    }

    /*
     * We could simply finish when there was nothing to read, and we have
     * nothing left to write. But keeping track of the expected number of bytes
     * to read gives us somewhat better guarantees that all data sent is in fact
     * received.
     */
    if (peer->bytes_to_write == 0 && peer->bytes_to_read == 0) {
        peer->status = PEER_SUCCESS;
    }
}