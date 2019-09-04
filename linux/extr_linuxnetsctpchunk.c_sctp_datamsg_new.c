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
struct sctp_datamsg {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datamsg ; 
 struct sctp_datamsg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_datamsg_init (struct sctp_datamsg*) ; 

__attribute__((used)) static struct sctp_datamsg *sctp_datamsg_new(gfp_t gfp)
{
	struct sctp_datamsg *msg;
	msg = kmalloc(sizeof(struct sctp_datamsg), gfp);
	if (msg) {
		sctp_datamsg_init(msg);
		SCTP_DBG_OBJCNT_INC(datamsg);
	}
	return msg;
}