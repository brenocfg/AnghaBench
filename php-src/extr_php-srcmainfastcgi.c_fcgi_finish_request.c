#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fd; } ;
typedef  TYPE_1__ fcgi_request ;

/* Variables and functions */
 int /*<<< orphan*/  fcgi_close (TYPE_1__*,int,int) ; 
 int fcgi_end (TYPE_1__*) ; 

int fcgi_finish_request(fcgi_request *req, int force_close)
{
	int ret = 1;

	if (req->fd >= 0) {
		ret = fcgi_end(req);
		fcgi_close(req, force_close, 1);
	}
	return ret;
}