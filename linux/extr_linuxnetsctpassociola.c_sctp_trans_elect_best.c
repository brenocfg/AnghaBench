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
typedef  scalar_t__ u8 ;
struct sctp_transport {int dummy; } ;

/* Variables and functions */
 struct sctp_transport* sctp_trans_elect_tie (struct sctp_transport*,struct sctp_transport*) ; 
 scalar_t__ sctp_trans_score (struct sctp_transport*) ; 

__attribute__((used)) static struct sctp_transport *sctp_trans_elect_best(struct sctp_transport *curr,
						    struct sctp_transport *best)
{
	u8 score_curr, score_best;

	if (best == NULL || curr == best)
		return curr;

	score_curr = sctp_trans_score(curr);
	score_best = sctp_trans_score(best);

	/* First, try a score-based selection if both transport states
	 * differ. If we're in a tie, lets try to make a more clever
	 * decision here based on error counts and last time heard.
	 */
	if (score_curr > score_best)
		return curr;
	else if (score_curr == score_best)
		return sctp_trans_elect_tie(best, curr);
	else
		return best;
}