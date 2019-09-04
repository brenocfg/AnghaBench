#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  host_attrs; } ;
struct srp_internal {int /*<<< orphan*/  rport_attr_cont; TYPE_1__ t; } ;
struct scsi_transport_template {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct srp_internal*) ; 
 struct srp_internal* to_srp_internal (struct scsi_transport_template*) ; 
 int /*<<< orphan*/  transport_container_unregister (int /*<<< orphan*/ *) ; 

void srp_release_transport(struct scsi_transport_template *t)
{
	struct srp_internal *i = to_srp_internal(t);

	transport_container_unregister(&i->t.host_attrs);
	transport_container_unregister(&i->rport_attr_cont);

	kfree(i);
}