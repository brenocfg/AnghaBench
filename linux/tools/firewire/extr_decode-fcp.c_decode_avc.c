#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct link_transaction {TYPE_3__* request; } ;
struct avc_opcode_info {char* name; TYPE_4__* fields; } ;
struct avc_frame {size_t opcode; size_t ctype; size_t subunit_type; int subunit_id; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_8__ {char* name; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_6__ {TYPE_1__ write_block; } ;
struct TYPE_7__ {TYPE_2__ packet; } ;

/* Variables and functions */
 char** ctype_names ; 
 struct avc_opcode_info* opcode_info ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,size_t) ; 
 char** subunit_type_names ; 

__attribute__((used)) static void
decode_avc(struct link_transaction *t)
{
	struct avc_frame *frame =
	    (struct avc_frame *) t->request->packet.write_block.data;
	const struct avc_opcode_info *info;
	const char *name;
	char buffer[32];
	int i;

	info = &opcode_info[frame->opcode];
	if (info->name == NULL) {
		snprintf(buffer, sizeof(buffer),
			 "(unknown opcode 0x%02x)", frame->opcode);
		name = buffer;
	} else {
		name = info->name;
	}

	printf("av/c %s, subunit_type=%s, subunit_id=%d, opcode=%s",
	    ctype_names[frame->ctype], subunit_type_names[frame->subunit_type],
	    frame->subunit_id, name);

	for (i = 0; info->fields[i].name != NULL; i++)
		printf(", %s", info->fields[i].name);

	printf("\n");
}