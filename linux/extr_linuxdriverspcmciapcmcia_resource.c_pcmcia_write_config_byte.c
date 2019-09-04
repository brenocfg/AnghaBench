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
struct pcmcia_device {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int pcmcia_access_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_write_cis_mem ; 

int pcmcia_write_config_byte(struct pcmcia_device *p_dev, off_t where, u8 val)
{
	return pcmcia_access_config(p_dev, where, &val, pcmcia_write_cis_mem);
}