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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__ g_server_list ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

void nfs41_server_list_init()
{
    list_init(&g_server_list.head);
    InitializeCriticalSection(&g_server_list.lock);
}