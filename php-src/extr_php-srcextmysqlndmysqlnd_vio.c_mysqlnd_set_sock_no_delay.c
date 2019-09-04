#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;
struct TYPE_5__ {int socket; } ;
typedef  TYPE_2__ php_netstream_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_RETURN (int) ; 
 int FAILURE ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
mysqlnd_set_sock_no_delay(php_stream * stream)
{
	int socketd = ((php_netstream_data_t*)stream->abstract)->socket;
	int ret = SUCCESS;
	int flag = 1;
	int result = setsockopt(socketd, IPPROTO_TCP,  TCP_NODELAY, (char *) &flag, sizeof(int));

	DBG_ENTER("mysqlnd_set_sock_no_delay");

	if (result == -1) {
		ret = FAILURE;
	}

	DBG_RETURN(ret);
}