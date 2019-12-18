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
struct servent {int s_port; } ;

/* Variables and functions */
 int atoi (char const*) ; 
 struct servent* getservbyname (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
port_from_servname(const char *servname)
{
    int port = 0;
    port = atoi(servname);
    if (port >0 && port < 65536)
    {
        return port;
    }

    struct  servent *service;
    service = getservbyname(servname, NULL);
    if (service)
    {
        return service->s_port;
    }

    return 0;
}