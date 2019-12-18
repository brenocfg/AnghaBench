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
struct remote_entry {scalar_t__ proto; scalar_t__ af; scalar_t__ remote_port; scalar_t__ remote; } ;
struct connection_entry {scalar_t__ proto; scalar_t__ af; scalar_t__ remote_port; scalar_t__ remote; } ;

/* Variables and functions */

__attribute__((used)) static void
connection_entry_load_re(struct connection_entry *ce, const struct remote_entry *re)
{
    if (re->remote)
    {
        ce->remote = re->remote;
    }
    if (re->remote_port)
    {
        ce->remote_port = re->remote_port;
    }
    if (re->proto >= 0)
    {
        ce->proto = re->proto;
    }
    if (re->af > 0)
    {
        ce->af = re->af;
    }
}