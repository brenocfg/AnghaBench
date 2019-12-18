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
typedef  scalar_t__ in_addr_t ;

/* Variables and functions */
 scalar_t__ const DHCP_END ; 
 scalar_t__ const DHCP_PAD ; 
 scalar_t__ const DHCP_ROUTER ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int const) ; 
 int /*<<< orphan*/  memset (scalar_t__*,scalar_t__ const,int const) ; 
 scalar_t__ ntohl (scalar_t__) ; 

__attribute__((used)) static in_addr_t
do_extract(struct dhcp *dhcp, int optlen)
{
    uint8_t *p = (uint8_t *) (dhcp + 1);
    int i;
    in_addr_t ret = 0;

    for (i = 0; i < optlen; )
    {
        const uint8_t type = p[i];
        const int room = optlen - i;
        if (type == DHCP_END)
        {
            break;
        }
        else if (type == DHCP_PAD)
        {
            ++i;
        }
        else if (type == DHCP_ROUTER)
        {
            if (room >= 2)
            {
                const int len = p[i+1]; /* get option length */
                if (len <= (room-2))
                {
                    /* get router IP address */
                    if (!ret && len >= 4 && (len & 3) == 0)
                    {
                        memcpy(&ret, p+i+2, 4);
                        ret = ntohl(ret);
                    }
                    {
                        /* delete the router option */
                        uint8_t *dest = p + i;
                        const int owlen = len + 2;        /* len of data to overwrite */
                        uint8_t *src = dest + owlen;
                        uint8_t *end = p + optlen;
                        const int movlen = end - src;
                        if (movlen > 0)
                        {
                            memmove(dest, src, movlen);   /* overwrite router option */
                        }
                        memset(end - owlen, DHCP_PAD, owlen); /* pad tail */
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        else                            /* some other option */
        {
            if (room >= 2)
            {
                const int len = p[i+1]; /* get option length */
                i += (len + 2);         /* advance to next option */
            }
            else
            {
                break;
            }
        }
    }
    return ret;
}