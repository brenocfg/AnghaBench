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
struct link_socket_actual {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 int addr_port_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
link_socket_actual_match(const struct link_socket_actual *a1, const struct link_socket_actual *a2)
{
    return addr_port_match(&a1->dest, &a2->dest);
}