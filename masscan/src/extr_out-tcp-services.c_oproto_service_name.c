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
struct protoent {int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 struct protoent* getprotobynumber (int) ; 
 char const** oproto_services ; 
 char* strdup (int /*<<< orphan*/ ) ; 

const char *
oproto_service_name(int port)
{
    if (oproto_services[port])
        return oproto_services[port];
    {
        struct protoent *result;
        
        result = getprotobynumber(port);
        
        if (result == 0)
            return "unknown";
        
        return oproto_services[port] = strdup(result->p_name);
    }
}