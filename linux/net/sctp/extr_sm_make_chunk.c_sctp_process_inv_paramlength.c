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
struct sctp_paramhdr {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_chunk_free (struct sctp_chunk*) ; 
 struct sctp_chunk* sctp_make_violation_paramlen (struct sctp_association const*,struct sctp_chunk const*,struct sctp_paramhdr*) ; 

__attribute__((used)) static int sctp_process_inv_paramlength(const struct sctp_association *asoc,
					struct sctp_paramhdr *param,
					const struct sctp_chunk *chunk,
					struct sctp_chunk **errp)
{
	/* This is a fatal error.  Any accumulated non-fatal errors are
	 * not reported.
	 */
	if (*errp)
		sctp_chunk_free(*errp);

	/* Create an error chunk and fill it in with our payload. */
	*errp = sctp_make_violation_paramlen(asoc, chunk, param);

	return 0;
}