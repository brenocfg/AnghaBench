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

__attribute__((used)) static void dgram_reset_rcv_timeout(BIO *b)
{
# if defined(SO_RCVTIMEO)
    bio_dgram_data *data = (bio_dgram_data *)b->ptr;

    /* Is a timer active? */
    if (data->next_timeout.tv_sec > 0 || data->next_timeout.tv_usec > 0) {
#  ifdef OPENSSL_SYS_WINDOWS
        int timeout = data->socket_timeout.tv_sec * 1000 +
            data->socket_timeout.tv_usec / 1000;
        if (setsockopt(b->num, SOL_SOCKET, SO_RCVTIMEO,
                       (void *)&timeout, sizeof(timeout)) < 0) {
            perror("setsockopt");
        }
#  else
        if (setsockopt
            (b->num, SOL_SOCKET, SO_RCVTIMEO, &(data->socket_timeout),
             sizeof(struct timeval)) < 0) {
            perror("setsockopt");
        }
#  endif
    }
# endif
}