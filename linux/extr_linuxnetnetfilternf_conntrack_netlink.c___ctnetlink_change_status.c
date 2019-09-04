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
struct nf_conn {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 unsigned long IPS_UNCHANGEABLE_MASK ; 
 unsigned int __IPS_MAX_BIT ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__ctnetlink_change_status(struct nf_conn *ct, unsigned long on,
			  unsigned long off)
{
	unsigned int bit;

	/* Ignore these unchangable bits */
	on &= ~IPS_UNCHANGEABLE_MASK;
	off &= ~IPS_UNCHANGEABLE_MASK;

	for (bit = 0; bit < __IPS_MAX_BIT; bit++) {
		if (on & (1 << bit))
			set_bit(bit, &ct->status);
		else if (off & (1 << bit))
			clear_bit(bit, &ct->status);
	}
}