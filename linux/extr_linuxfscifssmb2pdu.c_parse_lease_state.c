#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smb2_create_rsp {int /*<<< orphan*/  CreateContextsLength; int /*<<< orphan*/  CreateContextsOffset; } ;
struct create_context {int /*<<< orphan*/  Next; int /*<<< orphan*/  NameLength; int /*<<< orphan*/  NameOffset; } ;
struct TCP_Server_Info {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* parse_lease_buf ) (struct create_context*,unsigned int*,char*) ;} ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct create_context*,unsigned int*,char*) ; 

__attribute__((used)) static __u8
parse_lease_state(struct TCP_Server_Info *server, struct smb2_create_rsp *rsp,
		  unsigned int *epoch, char *lease_key)
{
	char *data_offset;
	struct create_context *cc;
	unsigned int next;
	unsigned int remaining;
	char *name;

	data_offset = (char *)rsp + le32_to_cpu(rsp->CreateContextsOffset);
	remaining = le32_to_cpu(rsp->CreateContextsLength);
	cc = (struct create_context *)data_offset;
	while (remaining >= sizeof(struct create_context)) {
		name = le16_to_cpu(cc->NameOffset) + (char *)cc;
		if (le16_to_cpu(cc->NameLength) == 4 &&
		    strncmp(name, "RqLs", 4) == 0)
			return server->ops->parse_lease_buf(cc, epoch,
							    lease_key);

		next = le32_to_cpu(cc->Next);
		if (!next)
			break;
		remaining -= next;
		cc = (struct create_context *)((char *)cc + next);
	}

	return 0;
}