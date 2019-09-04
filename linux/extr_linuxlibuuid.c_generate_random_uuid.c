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

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (unsigned char*,int) ; 

void generate_random_uuid(unsigned char uuid[16])
{
	get_random_bytes(uuid, 16);
	/* Set UUID version to 4 --- truly random generation */
	uuid[6] = (uuid[6] & 0x0F) | 0x40;
	/* Set the UUID variant to DCE */
	uuid[8] = (uuid[8] & 0x3F) | 0x80;
}