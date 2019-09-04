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
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ ENOTCONN ; 
 scalar_t__ errno ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 

__attribute__((used)) static inline int isPipe( int fd )
{
    char        achPeer[128];
    socklen_t   len = 128;
    if (( getpeername( fd, (struct sockaddr *)achPeer, &len ) != 0 )&&
        ( errno == ENOTCONN ))
        return 0;
    else
        return 1;
}