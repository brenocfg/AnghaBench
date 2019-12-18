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
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* private_free ) (TYPE_1__*) ;} ;
struct link_slave {int /*<<< orphan*/  list; scalar_t__ master; TYPE_1__ slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct link_slave*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct link_slave* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void slave_free(struct snd_kcontrol *kcontrol)
{
	struct link_slave *slave = snd_kcontrol_chip(kcontrol);
	if (slave->slave.private_free)
		slave->slave.private_free(&slave->slave);
	if (slave->master)
		list_del(&slave->list);
	kfree(slave);
}