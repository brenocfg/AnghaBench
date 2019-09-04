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
typedef  size_t u8 ;
struct qtnf_wmac {int dummy; } ;
struct qtnf_bus {struct qtnf_wmac** mac; } ;

/* Variables and functions */
 size_t QTNF_MAX_MAC ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 scalar_t__ unlikely (int) ; 

struct qtnf_wmac *qtnf_core_get_mac(const struct qtnf_bus *bus, u8 macid)
{
	struct qtnf_wmac *mac = NULL;

	if (unlikely(macid >= QTNF_MAX_MAC)) {
		pr_err("invalid MAC index %u\n", macid);
		return NULL;
	}

	mac = bus->mac[macid];

	if (unlikely(!mac)) {
		pr_err("MAC%u: not initialized\n", macid);
		return NULL;
	}

	return mac;
}