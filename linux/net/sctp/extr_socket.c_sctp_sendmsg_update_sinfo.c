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
struct sctp_sndrcvinfo {int sinfo_tsn; int /*<<< orphan*/  sinfo_ssn; int /*<<< orphan*/  sinfo_timetolive; int /*<<< orphan*/  sinfo_flags; int /*<<< orphan*/  sinfo_assoc_id; int /*<<< orphan*/  sinfo_context; int /*<<< orphan*/  sinfo_ppid; int /*<<< orphan*/  sinfo_stream; } ;
struct sctp_cmsgs {TYPE_1__* authinfo; int /*<<< orphan*/  prinfo; int /*<<< orphan*/  srinfo; int /*<<< orphan*/  sinfo; } ;
struct sctp_association {int /*<<< orphan*/  default_timetolive; int /*<<< orphan*/  default_flags; int /*<<< orphan*/  default_context; int /*<<< orphan*/  default_ppid; int /*<<< orphan*/  default_stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  auth_keynumber; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association*) ; 

__attribute__((used)) static void sctp_sendmsg_update_sinfo(struct sctp_association *asoc,
				      struct sctp_sndrcvinfo *sinfo,
				      struct sctp_cmsgs *cmsgs)
{
	if (!cmsgs->srinfo && !cmsgs->sinfo) {
		sinfo->sinfo_stream = asoc->default_stream;
		sinfo->sinfo_ppid = asoc->default_ppid;
		sinfo->sinfo_context = asoc->default_context;
		sinfo->sinfo_assoc_id = sctp_assoc2id(asoc);

		if (!cmsgs->prinfo)
			sinfo->sinfo_flags = asoc->default_flags;
	}

	if (!cmsgs->srinfo && !cmsgs->prinfo)
		sinfo->sinfo_timetolive = asoc->default_timetolive;

	if (cmsgs->authinfo) {
		/* Reuse sinfo_tsn to indicate that authinfo was set and
		 * sinfo_ssn to save the keyid on tx path.
		 */
		sinfo->sinfo_tsn = 1;
		sinfo->sinfo_ssn = cmsgs->authinfo->auth_keynumber;
	}
}