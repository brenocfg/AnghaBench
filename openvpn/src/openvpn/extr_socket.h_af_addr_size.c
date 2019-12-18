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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline int
af_addr_size(sa_family_t af)
{
    switch (af)
    {
        case AF_INET: return sizeof(struct sockaddr_in);

        case AF_INET6: return sizeof(struct sockaddr_in6);

        default:
#if 0
            /* could be called from socket_do_accept() with empty addr */
            msg(M_ERR, "Bad address family: %d\n", af);
            ASSERT(0);
#endif
            return 0;
    }
}