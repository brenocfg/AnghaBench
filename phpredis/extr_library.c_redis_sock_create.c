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
struct TYPE_4__ {long retry_interval; int persistent; int port; double timeout; double read_timeout; scalar_t__ reply_literal; scalar_t__ tcp_keepalive; scalar_t__ readonly; int /*<<< orphan*/  scan; int /*<<< orphan*/ * err; int /*<<< orphan*/ * pipeline_cmd; int /*<<< orphan*/ * current; int /*<<< orphan*/ * head; int /*<<< orphan*/  mode; scalar_t__ compression_level; int /*<<< orphan*/  compression; int /*<<< orphan*/  serializer; int /*<<< orphan*/ * persistent_id; scalar_t__ dbNumber; scalar_t__ watching; int /*<<< orphan*/  status; int /*<<< orphan*/ * stream; void* host; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC ; 
 int /*<<< orphan*/  REDIS_COMPRESSION_NONE ; 
 int /*<<< orphan*/  REDIS_SCAN_NORETRY ; 
 int /*<<< orphan*/  REDIS_SERIALIZER_NONE ; 
 int /*<<< orphan*/  REDIS_SOCK_STATUS_DISCONNECTED ; 
 TYPE_1__* ecalloc (int,int) ; 
 int strlen (char*) ; 
 void* zend_string_init (char*,int,int /*<<< orphan*/ ) ; 

RedisSock*
redis_sock_create(char *host, int host_len, int port,
                  double timeout, double read_timeout,
                  int persistent, char *persistent_id,
                  long retry_interval)
{
    RedisSock *redis_sock;

    redis_sock         = ecalloc(1, sizeof(RedisSock));
    redis_sock->host = zend_string_init(host, host_len, 0);
    redis_sock->stream = NULL;
    redis_sock->status = REDIS_SOCK_STATUS_DISCONNECTED;
    redis_sock->watching = 0;
    redis_sock->dbNumber = 0;
    redis_sock->retry_interval = retry_interval * 1000;
    redis_sock->persistent = persistent;
    redis_sock->persistent_id = NULL;

    if (persistent && persistent_id != NULL) {
        redis_sock->persistent_id = zend_string_init(persistent_id, strlen(persistent_id), 0);
    }

    redis_sock->port    = port;
    redis_sock->timeout = timeout;
    redis_sock->read_timeout = read_timeout;

    redis_sock->serializer = REDIS_SERIALIZER_NONE;
    redis_sock->compression = REDIS_COMPRESSION_NONE;
    redis_sock->compression_level = 0; /* default */
    redis_sock->mode = ATOMIC;
    redis_sock->head = NULL;
    redis_sock->current = NULL;

    redis_sock->pipeline_cmd = NULL;

    redis_sock->err = NULL;

    redis_sock->scan = REDIS_SCAN_NORETRY;

    redis_sock->readonly = 0;
    redis_sock->tcp_keepalive = 0;
    redis_sock->reply_literal = 0;

    return redis_sock;
}