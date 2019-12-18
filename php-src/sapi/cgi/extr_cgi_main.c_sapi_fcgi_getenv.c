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
 char* cgi_getenv_win32 (char*,size_t) ; 
 char* fcgi_getenv (int /*<<< orphan*/ *,char*,int) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  server_context ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *sapi_fcgi_getenv(char *name, size_t name_len)
{
	/* when php is started by mod_fastcgi, no regular environment
	 * is provided to PHP.  It is always sent to PHP at the start
	 * of a request.  So we have to do our own lookup to get env
	 * vars.  This could probably be faster somehow.  */
	fcgi_request *request = (fcgi_request*) SG(server_context);
	char *ret = fcgi_getenv(request, name, (int)name_len);

#ifndef PHP_WIN32
	if (ret) return ret;
	/*  if cgi, or fastcgi and not found in fcgi env
		check the regular environment */
	return getenv(name);
#else
	if (ret) {
		/* The functions outside here don't know, where does it come
			from. They'll need to free the returned memory as it's
			not necessary from the fcgi env. */
		return strdup(ret);
	}
	/*  if cgi, or fastcgi and not found in fcgi env
		check the regular environment */
	return cgi_getenv_win32(name, name_len);
#endif
}