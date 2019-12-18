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
struct datalink_proto {int /*<<< orphan*/  sap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct datalink_proto*) ; 
 int /*<<< orphan*/  llc_sap_put (int /*<<< orphan*/ ) ; 

void unregister_8022_client(struct datalink_proto *proto)
{
	llc_sap_put(proto->sap);
	kfree(proto);
}