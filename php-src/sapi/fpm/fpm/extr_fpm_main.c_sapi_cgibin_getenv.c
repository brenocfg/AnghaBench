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
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 char* fcgi_getenv (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ fpm_is_running ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static char *sapi_cgibin_getenv(char *name, size_t name_len) /* {{{ */
{
	/* if fpm has started, use fcgi env */
	if (fpm_is_running) {
		fcgi_request *request = (fcgi_request*) SG(server_context);
		return fcgi_getenv(request, name, name_len);
	}

	/* if fpm has not started yet, use std env */
	return getenv(name);
}