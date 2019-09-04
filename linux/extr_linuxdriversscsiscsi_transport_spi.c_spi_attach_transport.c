#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct spi_transport_attrs {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  match; int /*<<< orphan*/ * grp; int /*<<< orphan*/ * class; } ;
struct TYPE_6__ {TYPE_1__ ac; } ;
struct scsi_transport_template {int target_size; int host_size; TYPE_2__ host_attrs; TYPE_2__ target_attrs; } ;
struct spi_internal {struct scsi_transport_template t; struct spi_function_template* f; } ;
struct spi_host_attrs {int dummy; } ;
struct spi_function_template {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  class; } ;
struct TYPE_7__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  host_attribute_group ; 
 struct spi_internal* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ spi_host_class ; 
 int /*<<< orphan*/  spi_host_match ; 
 int /*<<< orphan*/  spi_target_match ; 
 TYPE_3__ spi_transport_class ; 
 int /*<<< orphan*/  target_attribute_group ; 
 int /*<<< orphan*/  transport_container_register (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

struct scsi_transport_template *
spi_attach_transport(struct spi_function_template *ft)
{
	struct spi_internal *i = kzalloc(sizeof(struct spi_internal),
					 GFP_KERNEL);

	if (unlikely(!i))
		return NULL;

	i->t.target_attrs.ac.class = &spi_transport_class.class;
	i->t.target_attrs.ac.grp = &target_attribute_group;
	i->t.target_attrs.ac.match = spi_target_match;
	transport_container_register(&i->t.target_attrs);
	i->t.target_size = sizeof(struct spi_transport_attrs);
	i->t.host_attrs.ac.class = &spi_host_class.class;
	i->t.host_attrs.ac.grp = &host_attribute_group;
	i->t.host_attrs.ac.match = spi_host_match;
	transport_container_register(&i->t.host_attrs);
	i->t.host_size = sizeof(struct spi_host_attrs);
	i->f = ft;

	return &i->t;
}