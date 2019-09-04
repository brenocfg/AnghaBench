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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int lwip_getaddrname (int,struct sockaddr*,int /*<<< orphan*/ *,int) ; 

int lwip_getsockname(int s, struct sockaddr *name, socklen_t *namelen)
{
    return lwip_getaddrname(s, name, namelen, 1);
}