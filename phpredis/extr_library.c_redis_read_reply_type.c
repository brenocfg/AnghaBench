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
typedef  int /*<<< orphan*/  inbuf ;
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ RedisSock ;
typedef  scalar_t__ REDIS_REPLY_TYPE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  REDIS_THROW_EXCEPTION (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_BULK ; 
 scalar_t__ TYPE_INT ; 
 scalar_t__ TYPE_MULTIBULK ; 
 long atol (char*) ; 
 scalar_t__ php_stream_getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * php_stream_gets (int /*<<< orphan*/ ,char*,int) ; 
 int redis_check_eof (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
redis_read_reply_type(RedisSock *redis_sock, REDIS_REPLY_TYPE *reply_type,
                      long *reply_info)
{
    // Make sure we haven't lost the connection, even trying to reconnect
    if(-1 == redis_check_eof(redis_sock, 0)) {
        // Failure
        *reply_type = EOF;
        return -1;
    }

    // Attempt to read the reply-type byte
    if((*reply_type = php_stream_getc(redis_sock->stream)) == EOF) {
        REDIS_THROW_EXCEPTION( "socket error on read socket", 0);
        return -1;
    }

    // If this is a BULK, MULTI BULK, or simply an INTEGER response, we can
    // extract the value or size info here
    if(*reply_type == TYPE_INT || *reply_type == TYPE_BULK ||
       *reply_type == TYPE_MULTIBULK)
    {
        // Buffer to hold size information
        char inbuf[255];

        /* Read up to our newline */
        if (php_stream_gets(redis_sock->stream, inbuf, sizeof(inbuf)) == NULL) {
            return -1;
        }

        /* Set our size response */
        *reply_info = atol(inbuf);
    }

    /* Success! */
    return 0;
}