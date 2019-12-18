#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; } ;
typedef  TYPE_1__ nfs4_stateid ;

/* Variables and functions */
#define  NFS4_DELEGATION_STATEID_TYPE 130 
#define  NFS4_LOCK_STATEID_TYPE 129 
#define  NFS4_OPEN_STATEID_TYPE 128 

__attribute__((used)) static const nfs4_stateid *
nfs4_recoverable_stateid(const nfs4_stateid *stateid)
{
	if (!stateid)
		return NULL;
	switch (stateid->type) {
	case NFS4_OPEN_STATEID_TYPE:
	case NFS4_LOCK_STATEID_TYPE:
	case NFS4_DELEGATION_STATEID_TYPE:
		return stateid;
	default:
		break;
	}
	return NULL;
}