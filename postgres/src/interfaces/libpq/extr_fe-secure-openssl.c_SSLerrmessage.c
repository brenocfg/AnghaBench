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

/* Variables and functions */
 char* ERR_reason_error_string (unsigned long) ; 
 int /*<<< orphan*/  SSL_ERR_LEN ; 
 char* libpq_gettext (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 char* ssl_nomem ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
SSLerrmessage(unsigned long ecode)
{
	const char *errreason;
	char	   *errbuf;

	errbuf = malloc(SSL_ERR_LEN);
	if (!errbuf)
		return ssl_nomem;
	if (ecode == 0)
	{
		snprintf(errbuf, SSL_ERR_LEN, libpq_gettext("no SSL error reported"));
		return errbuf;
	}
	errreason = ERR_reason_error_string(ecode);
	if (errreason != NULL)
	{
		strlcpy(errbuf, errreason, SSL_ERR_LEN);
		return errbuf;
	}
	snprintf(errbuf, SSL_ERR_LEN, libpq_gettext("SSL error code %lu"), ecode);
	return errbuf;
}