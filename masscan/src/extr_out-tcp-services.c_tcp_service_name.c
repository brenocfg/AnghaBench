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
struct servent {int /*<<< orphan*/  s_name; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct servent* getservbyport (int /*<<< orphan*/ ,char*) ; 
 int getservbyport_r (int /*<<< orphan*/ ,char*,struct servent*,char*,int,struct servent**) ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 char const** tcp_services ; 

const char *
tcp_service_name(int port)
{
    if (tcp_services[port])
        return tcp_services[port];

#ifdef __linux__
    int r;
    struct servent result_buf;
    struct servent *result;
    char buf[2048];
    
    r = getservbyport_r(htons(port), "tcp", &result_buf,buf, sizeof(buf), &result);
    
    /* ignore ERANGE - if the result can't fit in 2k, just return unknown */
    if (r != 0 || result == NULL)
        return "unknown";
    
    return tcp_services[port] = strdup(result_buf.s_name);
#else
    {
    struct servent *result;
    
    result = getservbyport(htons((unsigned short)port), "tcp");
    
    if (result == 0)
        return "unknown";
    
    return tcp_services[port] = strdup(result->s_name);
    }
#endif
}