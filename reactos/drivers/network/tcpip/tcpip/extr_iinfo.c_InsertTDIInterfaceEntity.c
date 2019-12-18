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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ PIP_INTERFACE ;

/* Variables and functions */
 int /*<<< orphan*/  AT_ARP ; 
 int /*<<< orphan*/  AT_ENTITY ; 
 int /*<<< orphan*/  AT_NULL ; 
 int /*<<< orphan*/  AddEntity (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_NL_ENTITY ; 
 int /*<<< orphan*/  CL_NL_IP ; 
 int /*<<< orphan*/  IF_ENTITY ; 
 int /*<<< orphan*/  IF_MIB ; 
 scalar_t__ Loopback ; 

VOID InsertTDIInterfaceEntity( PIP_INTERFACE Interface ) {
    AddEntity(IF_ENTITY, Interface, IF_MIB);

    AddEntity(AT_ENTITY, Interface,
              (Interface != Loopback) ? AT_ARP : AT_NULL);

    /* FIXME: This is probably wrong */
    AddEntity(CL_NL_ENTITY, Interface, CL_NL_IP);
}