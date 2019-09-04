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
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
struct __sctp_missing {int type; int /*<<< orphan*/  num_missing; } ;
typedef  int /*<<< orphan*/  report ;
typedef  enum sctp_param { ____Placeholder_sctp_param } sctp_param ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_ERROR_MISS_PARAM ; 
 int /*<<< orphan*/  SCTP_PAD4 (int) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct __sctp_missing*) ; 
 int /*<<< orphan*/  sctp_init_cause (struct sctp_chunk*,int /*<<< orphan*/ ,int) ; 
 struct sctp_chunk* sctp_make_op_error_space (struct sctp_association const*,struct sctp_chunk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_process_missing_param(const struct sctp_association *asoc,
				      enum sctp_param paramtype,
				      struct sctp_chunk *chunk,
				      struct sctp_chunk **errp)
{
	struct __sctp_missing report;
	__u16 len;

	len = SCTP_PAD4(sizeof(report));

	/* Make an ERROR chunk, preparing enough room for
	 * returning multiple unknown parameters.
	 */
	if (!*errp)
		*errp = sctp_make_op_error_space(asoc, chunk, len);

	if (*errp) {
		report.num_missing = htonl(1);
		report.type = paramtype;
		sctp_init_cause(*errp, SCTP_ERROR_MISS_PARAM,
				sizeof(report));
		sctp_addto_chunk(*errp, sizeof(report), &report);
	}

	/* Stop processing this chunk. */
	return 0;
}