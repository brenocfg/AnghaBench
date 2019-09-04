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
typedef  int /*<<< orphan*/  u16 ;
struct kern_ipc_perm {struct ipc_security_struct* security; } ;
struct ipc_security_struct {int /*<<< orphan*/  sid; int /*<<< orphan*/  sclass; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current_sid () ; 
 struct ipc_security_struct* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipc_alloc_security(struct kern_ipc_perm *perm,
			      u16 sclass)
{
	struct ipc_security_struct *isec;

	isec = kzalloc(sizeof(struct ipc_security_struct), GFP_KERNEL);
	if (!isec)
		return -ENOMEM;

	isec->sclass = sclass;
	isec->sid = current_sid();
	perm->security = isec;

	return 0;
}