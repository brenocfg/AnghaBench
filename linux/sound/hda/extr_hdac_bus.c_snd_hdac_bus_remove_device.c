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
struct hdac_device {size_t addr; int /*<<< orphan*/  list; struct hdac_bus* bus; } ;
struct hdac_bus {int /*<<< orphan*/  unsol_work; int /*<<< orphan*/  num_codecs; int /*<<< orphan*/  codec_powered; int /*<<< orphan*/ ** caddr_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

void snd_hdac_bus_remove_device(struct hdac_bus *bus,
				struct hdac_device *codec)
{
	WARN_ON(bus != codec->bus);
	if (list_empty(&codec->list))
		return;
	list_del_init(&codec->list);
	bus->caddr_tbl[codec->addr] = NULL;
	clear_bit(codec->addr, &bus->codec_powered);
	bus->num_codecs--;
	flush_work(&bus->unsol_work);
}