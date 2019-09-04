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
typedef  int s32 ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int EPERM ; 
#define  VMCI_ERROR_ALREADY_EXISTS 134 
#define  VMCI_ERROR_DUPLICATE_ENTRY 133 
#define  VMCI_ERROR_INVALID_ARGS 132 
#define  VMCI_ERROR_INVALID_RESOURCE 131 
#define  VMCI_ERROR_NO_ACCESS 130 
#define  VMCI_ERROR_NO_MEM 129 
#define  VMCI_ERROR_NO_RESOURCES 128 

__attribute__((used)) static s32 vmci_transport_error_to_vsock_error(s32 vmci_error)
{
	switch (vmci_error) {
	case VMCI_ERROR_NO_MEM:
		return -ENOMEM;
	case VMCI_ERROR_DUPLICATE_ENTRY:
	case VMCI_ERROR_ALREADY_EXISTS:
		return -EADDRINUSE;
	case VMCI_ERROR_NO_ACCESS:
		return -EPERM;
	case VMCI_ERROR_NO_RESOURCES:
		return -ENOBUFS;
	case VMCI_ERROR_INVALID_RESOURCE:
		return -EHOSTUNREACH;
	case VMCI_ERROR_INVALID_ARGS:
	default:
		break;
	}
	return -EINVAL;
}