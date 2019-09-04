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

/* Variables and functions */
 int /*<<< orphan*/  SCTP_ERROR_INV_PARAM ; 
 int /*<<< orphan*/  sctp_init_cause (struct sctp_chunk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_op_error_space (struct sctp_association const*,struct sctp_chunk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_process_inv_mandatory(const struct sctp_association *asoc,
				      struct sctp_chunk *chunk,
				      struct sctp_chunk **errp)
{
	/* Invalid Mandatory Parameter Error has no payload. */

	if (!*errp)
		*errp = sctp_make_op_error_space(asoc, chunk, 0);

	if (*errp)
		sctp_init_cause(*errp, SCTP_ERROR_INV_PARAM, 0);

	/* Stop processing this chunk. */
	return 0;
}