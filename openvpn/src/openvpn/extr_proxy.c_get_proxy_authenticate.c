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
typedef  int /*<<< orphan*/  socket_descriptor_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROXY ; 
 int HTTP_AUTH_BASIC ; 
 int HTTP_AUTH_DIGEST ; 
 int HTTP_AUTH_NONE ; 
 int HTTP_AUTH_NTLM ; 
 int /*<<< orphan*/  chomp (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  recv_line (int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ *,int volatile*) ; 
 char* string_alloc (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int
get_proxy_authenticate(socket_descriptor_t sd,
                       int timeout,
                       char **data,
                       volatile int *signal_received)
{
    char buf[256];
    int ret = HTTP_AUTH_NONE;
    while (true)
    {
        if (!recv_line(sd, buf, sizeof(buf), timeout, true, NULL, signal_received))
        {
            free(*data);
            *data = NULL;
            return HTTP_AUTH_NONE;
        }
        chomp(buf);
        if (!strlen(buf))
        {
            return ret;
        }
        if (ret == HTTP_AUTH_NONE && !strncmp(buf, "Proxy-Authenticate: ", 20))
        {
            if (!strncmp(buf+20, "Basic ", 6))
            {
                msg(D_PROXY, "PROXY AUTH BASIC: '%s'", buf);
                *data = string_alloc(buf+26, NULL);
                ret = HTTP_AUTH_BASIC;
            }
#if PROXY_DIGEST_AUTH
            else if (!strncmp(buf+20, "Digest ", 7))
            {
                msg(D_PROXY, "PROXY AUTH DIGEST: '%s'", buf);
                *data = string_alloc(buf+27, NULL);
                ret = HTTP_AUTH_DIGEST;
            }
#endif
#if NTLM
            else if (!strncmp(buf+20, "NTLM", 4))
            {
                msg(D_PROXY, "PROXY AUTH NTLM: '%s'", buf);
                *data = NULL;
                ret = HTTP_AUTH_NTLM;
            }
#endif
        }
    }
}