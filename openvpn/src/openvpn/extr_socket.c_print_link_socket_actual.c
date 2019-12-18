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
struct link_socket_actual {int dummy; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int PS_SHOW_PKTINFO ; 
 int PS_SHOW_PORT ; 
 char const* print_link_socket_actual_ex (struct link_socket_actual const*,char*,int,struct gc_arena*) ; 

const char *
print_link_socket_actual(const struct link_socket_actual *act, struct gc_arena *gc)
{
    return print_link_socket_actual_ex(act, ":", PS_SHOW_PORT|PS_SHOW_PKTINFO, gc);
}