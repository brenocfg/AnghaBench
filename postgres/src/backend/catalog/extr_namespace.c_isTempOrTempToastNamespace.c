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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ myTempNamespace ; 
 scalar_t__ myTempToastNamespace ; 

bool
isTempOrTempToastNamespace(Oid namespaceId)
{
	if (OidIsValid(myTempNamespace) &&
		(myTempNamespace == namespaceId || myTempToastNamespace == namespaceId))
		return true;
	return false;
}