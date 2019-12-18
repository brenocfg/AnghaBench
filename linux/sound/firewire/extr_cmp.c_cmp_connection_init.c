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
typedef  unsigned int u32 ;
struct fw_unit {int dummy; } ;
struct cmp_connection {int direction; int connected; unsigned int pcr_index; unsigned int max_speed; int /*<<< orphan*/  last_pcr_value; int /*<<< orphan*/  mutex; int /*<<< orphan*/  resources; } ;
typedef  enum cmp_direction { ____Placeholder_cmp_direction } cmp_direction ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MPR_PLUGS_MASK ; 
 unsigned int MPR_SPEED_MASK ; 
 unsigned int MPR_SPEED_SHIFT ; 
 unsigned int MPR_XSPEED_MASK ; 
 unsigned int MPR_XSPEED_SHIFT ; 
 unsigned int SCODE_BETA ; 
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int fw_iso_resources_init (int /*<<< orphan*/ *,struct fw_unit*) ; 
 int /*<<< orphan*/  mpr_address (struct cmp_connection*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_fw_transaction (struct fw_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int cmp_connection_init(struct cmp_connection *c,
			struct fw_unit *unit,
			enum cmp_direction direction,
			unsigned int pcr_index)
{
	__be32 mpr_be;
	u32 mpr;
	int err;

	c->direction = direction;
	err = snd_fw_transaction(unit, TCODE_READ_QUADLET_REQUEST,
				 mpr_address(c), &mpr_be, 4, 0);
	if (err < 0)
		return err;
	mpr = be32_to_cpu(mpr_be);

	if (pcr_index >= (mpr & MPR_PLUGS_MASK))
		return -EINVAL;

	err = fw_iso_resources_init(&c->resources, unit);
	if (err < 0)
		return err;

	c->connected = false;
	mutex_init(&c->mutex);
	c->last_pcr_value = cpu_to_be32(0x80000000);
	c->pcr_index = pcr_index;
	c->max_speed = (mpr & MPR_SPEED_MASK) >> MPR_SPEED_SHIFT;
	if (c->max_speed == SCODE_BETA)
		c->max_speed += (mpr & MPR_XSPEED_MASK) >> MPR_XSPEED_SHIFT;

	return 0;
}