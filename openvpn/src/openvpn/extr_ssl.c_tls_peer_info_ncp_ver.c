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
 int sscanf (char const*,char*,int*) ; 
 char* strstr (char const*,char*) ; 

int
tls_peer_info_ncp_ver(const char *peer_info)
{
    const char *ncpstr = peer_info ? strstr(peer_info, "IV_NCP=") : NULL;
    if (ncpstr)
    {
        int ncp = 0;
        int r = sscanf(ncpstr, "IV_NCP=%d", &ncp);
        if (r == 1)
        {
            return ncp;
        }
    }
    return 0;
}