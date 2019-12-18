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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct iaddr {int /*<<< orphan*/  iabuf; } ;

/* Variables and functions */
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

char *piaddr( struct iaddr addr ) {
    struct sockaddr_in sa;
    memcpy(&sa.sin_addr,addr.iabuf,sizeof(sa.sin_addr));
    return inet_ntoa( sa.sin_addr );
}