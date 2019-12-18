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
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_THROW_EXCEPTION (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (int) ; 
 scalar_t__ php_stream_eof (int /*<<< orphan*/ ) ; 
 size_t php_stream_read (int /*<<< orphan*/ ,char*,int) ; 
 int redis_check_eof (TYPE_1__*,int /*<<< orphan*/ ) ; 

char *
redis_sock_read_bulk_reply(RedisSock *redis_sock, int bytes)
{
    int offset = 0, nbytes;
    char *reply;
    size_t got;

    if (-1 == bytes || -1 == redis_check_eof(redis_sock, 0)) {
        return NULL;
    }

    nbytes = bytes + 2;
    /* Allocate memory for string */
    reply = emalloc(nbytes);

    /* Consume bulk string */
    while (offset < nbytes) {
        got = php_stream_read(redis_sock->stream, reply + offset, nbytes - offset);
        if (got == 0 && php_stream_eof(redis_sock->stream)) break;
        offset += got;
    }

    /* Protect against reading too few bytes */
    if (offset < nbytes) {
        /* Error or EOF */
        REDIS_THROW_EXCEPTION("socket error on read socket", 0);
        efree(reply);
        return NULL;
    }

    /* Null terminate reply string */
    reply[bytes] = '\0';

    return reply;
}