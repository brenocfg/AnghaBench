#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sa; } ;
struct openvpn_sockaddr {TYPE_1__ addr; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_SHOW_PORT ; 
 char const* print_sockaddr_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct gc_arena*) ; 

__attribute__((used)) static inline
const char *
print_openvpn_sockaddr(const struct openvpn_sockaddr *addr,
                       struct gc_arena *gc)
{
    return print_sockaddr_ex(&addr->addr.sa, ":", PS_SHOW_PORT, gc);
}