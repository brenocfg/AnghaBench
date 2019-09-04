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

/* Variables and functions */
 unsigned int INT_IN_EP ; 
 unsigned int ISOC_IN_EP ; 

__attribute__((used)) static bool xhci_is_sync_in_ep(unsigned int ep_type)
{
	return (ep_type == ISOC_IN_EP || ep_type == INT_IN_EP);
}