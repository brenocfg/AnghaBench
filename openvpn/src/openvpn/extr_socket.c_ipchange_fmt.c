#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct link_socket_info {int /*<<< orphan*/  ipchange_command; TYPE_4__* lsa; } ;
struct gc_arena {int dummy; } ;
struct argv {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sa; } ;
struct TYPE_6__ {TYPE_1__ addr; } ;
struct TYPE_7__ {TYPE_2__ dest; } ;
struct TYPE_8__ {TYPE_3__ actual; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_SHOW_PORT ; 
 int /*<<< orphan*/  argv_parse_cmd (struct argv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,char const*) ; 
 int /*<<< orphan*/  argv_printf_cat (struct argv*,char*,char const*) ; 
 char* print_sockaddr_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct gc_arena*) ; 

__attribute__((used)) static void
ipchange_fmt(const bool include_cmd, struct argv *argv, const struct link_socket_info *info, struct gc_arena *gc)
{
    const char *host = print_sockaddr_ex(&info->lsa->actual.dest.addr.sa, " ", PS_SHOW_PORT, gc);
    if (include_cmd)
    {
        argv_parse_cmd(argv, info->ipchange_command);
        argv_printf_cat(argv, "%s", host);
    }
    else
    {
        argv_printf(argv, "%s", host);
    }

}