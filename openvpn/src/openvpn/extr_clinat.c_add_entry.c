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
struct client_nat_option_list {scalar_t__ n; struct client_nat_entry* entries; } ;
struct client_nat_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_CLIENT_NAT ; 
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static bool
add_entry(struct client_nat_option_list *dest,
          const struct client_nat_entry *e)
{
    if (dest->n >= MAX_CLIENT_NAT)
    {
        msg(M_WARN, "WARNING: client-nat table overflow (max %d entries)", MAX_CLIENT_NAT);
        return false;
    }
    else
    {
        dest->entries[dest->n++] = *e;
        return true;
    }
}