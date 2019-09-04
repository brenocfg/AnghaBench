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
struct via_aux_drv {TYPE_1__* bus; int /*<<< orphan*/  chain; } ;
struct TYPE_2__ {int /*<<< orphan*/  drivers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct via_aux_drv* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool via_aux_add(struct via_aux_drv *drv)
{
	struct via_aux_drv *data = kmalloc(sizeof(*data), GFP_KERNEL);

	if (!data)
		return false;

	*data = *drv;
	list_add_tail(&data->chain, &data->bus->drivers);
	return true;
}