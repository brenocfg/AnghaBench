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
struct domain_device {scalar_t__ dev_type; } ;

/* Variables and functions */
 scalar_t__ SAS_EDGE_EXPANDER_DEVICE ; 
 scalar_t__ SAS_FANOUT_EXPANDER_DEVICE ; 

__attribute__((used)) static inline bool dev_is_expander(struct domain_device *dev)
{
	return dev->dev_type == SAS_EDGE_EXPANDER_DEVICE || dev->dev_type == SAS_FANOUT_EXPANDER_DEVICE;
}