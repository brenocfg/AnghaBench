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
struct iovec {unsigned int iov_len; char* iov_base; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ g_running ; 
 scalar_t__ s_skip_write ; 
 int writev (int,struct iovec*,int) ; 

__attribute__((used)) static int lsapi_writev( int fd, struct iovec ** pVec, int count, int totalLen )
{
    int ret;
    int left = totalLen;
    int n = count;

    if (s_skip_write)
        return totalLen;

    while(( left > 0 )&&g_running )
    {
        ret = writev( fd, *pVec, n );
        if ( ret > 0 )
        {
            left -= ret;
            if (( left <= 0)||( !g_running ))
                return totalLen - left;
            while( ret > 0 )
            {
                if ( (*pVec)->iov_len <= (unsigned int )ret )
                {
                    ret -= (*pVec)->iov_len;
                    ++(*pVec);
                }
                else
                {
                    (*pVec)->iov_base = (char *)(*pVec)->iov_base + ret;
                    (*pVec)->iov_len -= ret;
                    break;
                }
            }
        }
        else if ( ret == -1 )
        {
            if ( errno == EAGAIN )
            {
                if ( totalLen - left > 0 )
                    return totalLen - left;
                else
                    return -1;
            }
            else if ( errno != EINTR )
                return ret;
        }
    }
    return totalLen - left;
}