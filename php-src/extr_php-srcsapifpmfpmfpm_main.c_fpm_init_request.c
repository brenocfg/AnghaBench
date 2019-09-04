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
typedef  int /*<<< orphan*/  fcgi_request ;

/* Variables and functions */
 int /*<<< orphan*/ * fcgi_init_request (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_request_accepting ; 
 int /*<<< orphan*/  fpm_request_finished ; 
 int /*<<< orphan*/  fpm_request_reading_headers ; 

__attribute__((used)) static fcgi_request *fpm_init_request(int listen_fd) /* {{{ */ {
	fcgi_request *req = fcgi_init_request(listen_fd,
		fpm_request_accepting,
		fpm_request_reading_headers,
		fpm_request_finished);
	return req;
}