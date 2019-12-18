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
struct nfs4_ace {int whotype; int flag; } ;

/* Variables and functions */
 short ACL_GROUP ; 
 short ACL_GROUP_OBJ ; 
 short ACL_OTHER ; 
 short ACL_USER ; 
 short ACL_USER_OBJ ; 
 int /*<<< orphan*/  BUG () ; 
 int NFS4_ACE_IDENTIFIER_GROUP ; 
#define  NFS4_ACL_WHO_EVERYONE 131 
#define  NFS4_ACL_WHO_GROUP 130 
#define  NFS4_ACL_WHO_NAMED 129 
#define  NFS4_ACL_WHO_OWNER 128 

__attribute__((used)) static short
ace2type(struct nfs4_ace *ace)
{
	switch (ace->whotype) {
		case NFS4_ACL_WHO_NAMED:
			return (ace->flag & NFS4_ACE_IDENTIFIER_GROUP ?
					ACL_GROUP : ACL_USER);
		case NFS4_ACL_WHO_OWNER:
			return ACL_USER_OBJ;
		case NFS4_ACL_WHO_GROUP:
			return ACL_GROUP_OBJ;
		case NFS4_ACL_WHO_EVERYONE:
			return ACL_OTHER;
	}
	BUG();
	return -1;
}