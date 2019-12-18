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
typedef  enum OID { ____Placeholder_OID } OID ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBADMSG ; 
 int OID__NR ; 
 scalar_t__ oid_data ; 
 scalar_t__* oid_index ; 
 int sprint_oid (scalar_t__,scalar_t__,char*,size_t) ; 

int sprint_OID(enum OID oid, char *buffer, size_t bufsize)
{
	int ret;

	BUG_ON(oid >= OID__NR);

	ret = sprint_oid(oid_data + oid_index[oid],
			 oid_index[oid + 1] - oid_index[oid],
			 buffer, bufsize);
	BUG_ON(ret == -EBADMSG);
	return ret;
}