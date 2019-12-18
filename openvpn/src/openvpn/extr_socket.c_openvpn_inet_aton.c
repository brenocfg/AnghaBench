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
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int CC_DIGIT ; 
 int CC_DOT ; 
 int /*<<< orphan*/  CLEAR (struct in_addr) ; 
 int OIA_ERROR ; 
 int OIA_HOSTNAME ; 
 int OIA_IP ; 
 int /*<<< orphan*/  htonl (unsigned int) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 scalar_t__ string_class (char const*,int,int /*<<< orphan*/ ) ; 

int
openvpn_inet_aton(const char *dotted_quad, struct in_addr *addr)
{
    unsigned int a, b, c, d;

    CLEAR(*addr);
    if (sscanf(dotted_quad, "%u.%u.%u.%u", &a, &b, &c, &d) == 4)
    {
        if (a < 256 && b < 256 && c < 256 && d < 256)
        {
            addr->s_addr = htonl(a<<24 | b<<16 | c<<8 | d);
            return OIA_IP; /* good dotted quad */
        }
    }
    if (string_class(dotted_quad, CC_DIGIT|CC_DOT, 0))
    {
        return OIA_ERROR; /* probably a badly formatted dotted quad */
    }
    else
    {
        return OIA_HOSTNAME; /* probably a hostname */
    }
}