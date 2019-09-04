#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gfs2_sbd {int dummy; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct gfs2_quota_data {TYPE_3__ qd_id; TYPE_2__* qd_gl; } ;
struct TYPE_4__ {struct gfs2_sbd* ln_sbd; } ;
struct TYPE_5__ {TYPE_1__ gl_name; } ;

/* Variables and functions */
 scalar_t__ USRQUOTA ; 
 int /*<<< orphan*/  from_kqid (int /*<<< orphan*/ *,TYPE_3__) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 

__attribute__((used)) static int print_message(struct gfs2_quota_data *qd, char *type)
{
	struct gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;

	fs_info(sdp, "quota %s for %s %u\n",
		type,
		(qd->qd_id.type == USRQUOTA) ? "user" : "group",
		from_kqid(&init_user_ns, qd->qd_id));

	return 0;
}