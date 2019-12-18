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
typedef  scalar_t__ uint8_t ;
struct dhcp {int dummy; } ;

/* Variables and functions */
 scalar_t__ const DHCP_END ; 
 scalar_t__ const DHCP_MSG_TYPE ; 
 scalar_t__ const DHCP_PAD ; 

__attribute__((used)) static int
get_dhcp_message_type(const struct dhcp *dhcp, const int optlen)
{
    const uint8_t *p = (uint8_t *) (dhcp + 1);
    int i;

    for (i = 0; i < optlen; ++i)
    {
        const uint8_t type = p[i];
        const int room = optlen - i;
        if (type == DHCP_END)         /* didn't find what we were looking for */
        {
            return -1;
        }
        else if (type == DHCP_PAD)    /* no-operation */
        {
        }
        else if (type == DHCP_MSG_TYPE) /* what we are looking for */
        {
            if (room >= 3)
            {
                if (p[i+1] == 1)      /* option length should be 1 */
                {
                    return p[i+2];    /* return message type */
                }
            }
            return -1;
        }
        else                          /* some other option */
        {
            if (room >= 2)
            {
                const int len = p[i+1]; /* get option length */
                i += (len + 1);       /* advance to next option */
            }
        }
    }
    return -1;
}