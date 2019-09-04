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
typedef  int /*<<< orphan*/  u8 ;
struct ssb_bus {int /*<<< orphan*/  host_pcmcia; } ;

/* Variables and functions */
 int EBUSY ; 
 int pcmcia_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ssb_pcmcia_cfg_write(struct ssb_bus *bus, u8 offset, u8 value)
{
	int res;

	res = pcmcia_write_config_byte(bus->host_pcmcia, offset, value);
	if (unlikely(res != 0))
		return -EBUSY;

	return 0;
}