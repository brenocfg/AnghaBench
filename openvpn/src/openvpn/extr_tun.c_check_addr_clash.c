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
struct gc_arena {int dummy; } ;
typedef  int in_addr_t ;

/* Variables and functions */
 int DEV_TYPE_TAP ; 
 int DEV_TYPE_TUN ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  ifconfig_warn_how_to_silence ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_in_addr_t (int,int /*<<< orphan*/ ,struct gc_arena*) ; 

__attribute__((used)) static void
check_addr_clash(const char *name,
                 int type,
                 in_addr_t public,
                 in_addr_t local,
                 in_addr_t remote_netmask)
{
    struct gc_arena gc = gc_new();
#if 0
    msg(M_INFO, "CHECK_ADDR_CLASH type=%d public=%s local=%s, remote_netmask=%s",
        type,
        print_in_addr_t(public, 0, &gc),
        print_in_addr_t(local, 0, &gc),
        print_in_addr_t(remote_netmask, 0, &gc));
#endif

    if (public)
    {
        if (type == DEV_TYPE_TUN)
        {
            const in_addr_t test_netmask = 0xFFFFFF00;
            const in_addr_t public_net = public & test_netmask;
            const in_addr_t local_net = local & test_netmask;
            const in_addr_t remote_net = remote_netmask & test_netmask;

            if (public == local || public == remote_netmask)
            {
                msg(M_WARN,
                    "WARNING: --%s address [%s] conflicts with --ifconfig address pair [%s, %s]. %s",
                    name,
                    print_in_addr_t(public, 0, &gc),
                    print_in_addr_t(local, 0, &gc),
                    print_in_addr_t(remote_netmask, 0, &gc),
                    ifconfig_warn_how_to_silence);
            }

            if (public_net == local_net || public_net == remote_net)
            {
                msg(M_WARN,
                    "WARNING: potential conflict between --%s address [%s] and --ifconfig address pair [%s, %s] -- this is a warning only that is triggered when local/remote addresses exist within the same /24 subnet as --ifconfig endpoints. %s",
                    name,
                    print_in_addr_t(public, 0, &gc),
                    print_in_addr_t(local, 0, &gc),
                    print_in_addr_t(remote_netmask, 0, &gc),
                    ifconfig_warn_how_to_silence);
            }
        }
        else if (type == DEV_TYPE_TAP)
        {
            const in_addr_t public_network = public & remote_netmask;
            const in_addr_t virtual_network = local & remote_netmask;
            if (public_network == virtual_network)
            {
                msg(M_WARN,
                    "WARNING: --%s address [%s] conflicts with --ifconfig subnet [%s, %s] -- local and remote addresses cannot be inside of the --ifconfig subnet. %s",
                    name,
                    print_in_addr_t(public, 0, &gc),
                    print_in_addr_t(local, 0, &gc),
                    print_in_addr_t(remote_netmask, 0, &gc),
                    ifconfig_warn_how_to_silence);
            }
        }
    }
    gc_free(&gc);
}