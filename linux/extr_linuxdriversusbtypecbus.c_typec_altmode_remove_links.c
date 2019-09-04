#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_10__ {TYPE_4__ dev; } ;
struct altmode {TYPE_5__ adev; TYPE_3__* partner; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;
struct TYPE_8__ {TYPE_2__ adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void typec_altmode_remove_links(struct altmode *alt)
{
	sysfs_remove_link(&alt->partner->adev.dev.kobj, "partner");
	sysfs_remove_link(&alt->adev.dev.kobj, "port");
}