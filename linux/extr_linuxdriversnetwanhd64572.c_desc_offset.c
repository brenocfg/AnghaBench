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
typedef  int u16 ;
typedef  int /*<<< orphan*/  port_t ;
typedef  int /*<<< orphan*/  pkt_desc ;

/* Variables and functions */
 int desc_abs_number (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline u16 desc_offset(port_t *port, u16 desc, int transmit)
{
	/* Descriptor offset always fits in 16 bits */
	return desc_abs_number(port, desc, transmit) * sizeof(pkt_desc);
}