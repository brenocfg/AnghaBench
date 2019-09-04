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
struct snd_us16x08_meter_store {int comp_index; scalar_t__ comp_active_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_us16x08_meter_store* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_us16x08_meter_store *snd_us16x08_create_meter_store(void)
{
	struct snd_us16x08_meter_store *tmp;

	tmp = kzalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return NULL;
	tmp->comp_index = 1;
	tmp->comp_active_index = 0;
	return tmp;
}