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
 int SADB_ADD ; 
 int SADB_DELETE ; 
 int SADB_EXPIRE ; 
 int SADB_UPDATE ; 
#define  XFRM_MSG_DELSA 131 
#define  XFRM_MSG_EXPIRE 130 
#define  XFRM_MSG_NEWSA 129 
#define  XFRM_MSG_UPDSA 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static inline int event2keytype(int event)
{
	switch (event) {
	case XFRM_MSG_DELSA:
		return SADB_DELETE;
	case XFRM_MSG_NEWSA:
		return SADB_ADD;
	case XFRM_MSG_UPDSA:
		return SADB_UPDATE;
	case XFRM_MSG_EXPIRE:
		return SADB_EXPIRE;
	default:
		pr_err("pfkey: Unknown SA event %d\n", event);
		break;
	}

	return 0;
}