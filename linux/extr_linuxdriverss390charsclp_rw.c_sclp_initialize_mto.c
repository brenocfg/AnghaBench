#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sclp_buffer {char* current_line; scalar_t__ current_length; struct msg_buf* current_msg; struct sccb_header* sccb; } ;
struct sccb_header {int length; } ;
struct mto {int length; int type; int /*<<< orphan*/  line_type_flags; } ;
struct go {int length; int type; } ;
struct TYPE_4__ {int length; int type; int tag; int revision_code; } ;
struct mdb {struct mto mto; struct go go; TYPE_2__ header; } ;
struct TYPE_3__ {int length; int /*<<< orphan*/  type; } ;
struct msg_buf {struct mdb mdb; TYPE_1__ header; } ;
typedef  int addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVTYP_MSG ; 
 int /*<<< orphan*/  LNTPFLGS_ENDTEXT ; 
 int MAX_SCCB_ROOM ; 
 int /*<<< orphan*/  memset (struct msg_buf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sclp_initialize_mto(struct sclp_buffer *buffer, int max_len)
{
	struct sccb_header *sccb;
	struct msg_buf *msg;
	struct mdb *mdb;
	struct go *go;
	struct mto *mto;
	int msg_size;

	/* max size of new message including message text  */
	msg_size = sizeof(struct msg_buf) + max_len;

	/* check if current buffer sccb can contain the mto */
	sccb = buffer->sccb;
	if ((MAX_SCCB_ROOM - sccb->length) < msg_size)
		return -ENOMEM;

	msg = (struct msg_buf *)((addr_t) sccb + sccb->length);
	memset(msg, 0, sizeof(struct msg_buf));
	msg->header.length = sizeof(struct msg_buf);
	msg->header.type = EVTYP_MSG;

	mdb = &msg->mdb;
	mdb->header.length = sizeof(struct mdb);
	mdb->header.type = 1;
	mdb->header.tag = 0xD4C4C240;	/* ebcdic "MDB " */
	mdb->header.revision_code = 1;

	go = &mdb->go;
	go->length = sizeof(struct go);
	go->type = 1;

	mto = &mdb->mto;
	mto->length = sizeof(struct mto);
	mto->type = 4;	/* message text object */
	mto->line_type_flags = LNTPFLGS_ENDTEXT; /* end text */

	/* set pointer to first byte after struct mto. */
	buffer->current_msg = msg;
	buffer->current_line = (char *) (mto + 1);
	buffer->current_length = 0;

	return 0;
}