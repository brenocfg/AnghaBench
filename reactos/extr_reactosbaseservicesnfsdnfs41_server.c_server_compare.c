#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct server_info {int /*<<< orphan*/  owner; int /*<<< orphan*/  scope; } ;
struct list_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  scope; } ;
typedef  TYPE_1__ nfs41_server ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 TYPE_1__* server_entry (struct list_entry const*) ; 
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int server_compare(
    const struct list_entry *entry,
    const void *value)
{
    const nfs41_server *server = server_entry(entry);
    const struct server_info *info = (const struct server_info*)value;
    const int diff = strncmp(server->scope, info->scope, NFS4_OPAQUE_LIMIT);
    return diff ? diff : strncmp(server->owner, info->owner, NFS4_OPAQUE_LIMIT);
}