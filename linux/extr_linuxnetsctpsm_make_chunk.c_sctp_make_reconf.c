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
struct sctp_reconf_chunk {int /*<<< orphan*/  params; } ;
struct TYPE_2__ {int /*<<< orphan*/  v; } ;
struct sctp_chunk {TYPE_1__ param_hdr; scalar_t__ chunk_hdr; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_CID_RECONF ; 
 struct sctp_chunk* sctp_make_control (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_chunk *sctp_make_reconf(const struct sctp_association *asoc,
					   int length)
{
	struct sctp_reconf_chunk *reconf;
	struct sctp_chunk *retval;

	retval = sctp_make_control(asoc, SCTP_CID_RECONF, 0, length,
				   GFP_ATOMIC);
	if (!retval)
		return NULL;

	reconf = (struct sctp_reconf_chunk *)retval->chunk_hdr;
	retval->param_hdr.v = reconf->params;

	return retval;
}