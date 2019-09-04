#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_stream ;
typedef  scalar_t__ php_socket_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_11__ {TYPE_2__* data; } ;
struct TYPE_10__ {TYPE_3__* data; } ;
struct TYPE_9__ {int /*<<< orphan*/  thread_id; TYPE_5__* vio; } ;
struct TYPE_7__ {int /*<<< orphan*/ * (* get_stream ) (TYPE_5__*) ;} ;
struct TYPE_8__ {TYPE_1__ m; } ;
typedef  TYPE_4__ MYSQLND ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBG_RETURN (int) ; 
 int /*<<< orphan*/  PHP_SAFE_FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int PHP_STREAM_AS_FD_FOR_SELECT ; 
 int PHP_STREAM_CAST_INTERNAL ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ ZEND_VALID_SOCKET (scalar_t__) ; 
 scalar_t__ php_stream_cast (int /*<<< orphan*/ *,int,void*,int) ; 
 int /*<<< orphan*/ * stub1 (TYPE_5__*) ; 

__attribute__((used)) static unsigned int
mysqlnd_stream_array_to_fd_set(MYSQLND ** conn_array, fd_set * fds, php_socket_t * max_fd)
{
	php_socket_t this_fd;
	php_stream *stream = NULL;
	unsigned int cnt = 0;
	MYSQLND **p = conn_array;
	DBG_ENTER("mysqlnd_stream_array_to_fd_set");

	while (*p) {
		/* get the fd.
		 * NB: Most other code will NOT use the PHP_STREAM_CAST_INTERNAL flag
		 * when casting.  It is only used here so that the buffered data warning
		 * is not displayed.
		 * */
		stream = (*p)->data->vio->data->m.get_stream((*p)->data->vio);
		DBG_INF_FMT("conn=%llu stream=%p", (*p)->data->thread_id, stream);
		if (stream != NULL &&
			SUCCESS == php_stream_cast(stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL, (void*)&this_fd, 1) &&
			ZEND_VALID_SOCKET(this_fd))
		{

			PHP_SAFE_FD_SET(this_fd, fds);

			if (this_fd > *max_fd) {
				*max_fd = this_fd;
			}
			++cnt;
		}
		++p;
	}
	DBG_RETURN(cnt ? 1 : 0);
}