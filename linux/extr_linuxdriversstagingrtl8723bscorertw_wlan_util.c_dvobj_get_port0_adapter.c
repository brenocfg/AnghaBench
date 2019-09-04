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
struct dvobj_priv {struct adapter* padapters; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ IFACE_PORT0 ; 
 scalar_t__ get_iface_type (struct adapter) ; 
 size_t i ; 

struct adapter *dvobj_get_port0_adapter(struct dvobj_priv *dvobj)
{
	if (get_iface_type(dvobj->padapters[i]) != IFACE_PORT0)
		return NULL;

	return dvobj->padapters;
}