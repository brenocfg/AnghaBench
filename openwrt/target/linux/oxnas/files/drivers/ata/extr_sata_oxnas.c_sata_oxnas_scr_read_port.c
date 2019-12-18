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
typedef  int /*<<< orphan*/  u32 ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sata_oxnas_link_read (struct ata_port*,int) ; 

__attribute__((used)) static int sata_oxnas_scr_read_port(struct ata_port *ap, unsigned int sc_reg,
					u32 *val)
{
	*val = sata_oxnas_link_read(ap, 0x20 + (sc_reg*4));
	return 0;
}