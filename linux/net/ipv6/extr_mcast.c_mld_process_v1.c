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
struct mld_msg {int /*<<< orphan*/  mld_maxdelay; } ;
struct inet6_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLDV1_MRD_MAX_COMPAT ; 
 unsigned long max (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mld_clear_delrec (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_gq_stop_timer (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_ifc_stop_timer (struct inet6_dev*) ; 
 scalar_t__ mld_in_v2_mode_only (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_set_v1_mode (struct inet6_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 unsigned long ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mld_process_v1(struct inet6_dev *idev, struct mld_msg *mld,
			  unsigned long *max_delay, bool v1_query)
{
	unsigned long mldv1_md;

	/* Ignore v1 queries */
	if (mld_in_v2_mode_only(idev))
		return -EINVAL;

	mldv1_md = ntohs(mld->mld_maxdelay);

	/* When in MLDv1 fallback and a MLDv2 router start-up being
	 * unaware of current MLDv1 operation, the MRC == MRD mapping
	 * only works when the exponential algorithm is not being
	 * used (as MLDv1 is unaware of such things).
	 *
	 * According to the RFC author, the MLDv2 implementations
	 * he's aware of all use a MRC < 32768 on start up queries.
	 *
	 * Thus, should we *ever* encounter something else larger
	 * than that, just assume the maximum possible within our
	 * reach.
	 */
	if (!v1_query)
		mldv1_md = min(mldv1_md, MLDV1_MRD_MAX_COMPAT);

	*max_delay = max(msecs_to_jiffies(mldv1_md), 1UL);

	/* MLDv1 router present: we need to go into v1 mode *only*
	 * when an MLDv1 query is received as per section 9.12. of
	 * RFC3810! And we know from RFC2710 section 3.7 that MLDv1
	 * queries MUST be of exactly 24 octets.
	 */
	if (v1_query)
		mld_set_v1_mode(idev);

	/* cancel MLDv2 report timer */
	mld_gq_stop_timer(idev);
	/* cancel the interface change timer */
	mld_ifc_stop_timer(idev);
	/* clear deleted report items */
	mld_clear_delrec(idev);

	return 0;
}