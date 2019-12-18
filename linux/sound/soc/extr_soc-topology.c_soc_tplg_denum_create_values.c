#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int* dvalues; } ;
struct TYPE_4__ {TYPE_1__ control; } ;
struct soc_enum {TYPE_2__ dobj; } ;
struct snd_soc_tplg_enum_control {int /*<<< orphan*/ * values; int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_tplg_denum_create_values(struct soc_enum *se,
	struct snd_soc_tplg_enum_control *ec)
{
	int i;

	if (le32_to_cpu(ec->items) > sizeof(*ec->values))
		return -EINVAL;

	se->dobj.control.dvalues = kzalloc(le32_to_cpu(ec->items) *
					   sizeof(u32),
					   GFP_KERNEL);
	if (!se->dobj.control.dvalues)
		return -ENOMEM;

	/* convert from little-endian */
	for (i = 0; i < le32_to_cpu(ec->items); i++) {
		se->dobj.control.dvalues[i] = le32_to_cpu(ec->values[i]);
	}

	return 0;
}