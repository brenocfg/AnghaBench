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
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ g_running ; 
 int read (int,char*,size_t) ; 

__attribute__((used)) static inline ssize_t lsapi_read( int fd, void * pBuf, size_t len )
{
    ssize_t ret;
    while( 1 )
    {
        ret = read( fd, (char *)pBuf, len );
        if (( ret == -1 )&&( errno == EINTR )&&(g_running))
            continue;
        return ret;
    }
}