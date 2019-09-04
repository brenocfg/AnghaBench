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
struct lowpan_nhc {scalar_t__ idlen; size_t nexthdr; int /*<<< orphan*/  (* idsetup ) (struct lowpan_nhc*) ;} ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ LOWPAN_NHC_MAX_ID_LEN ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,scalar_t__) ; 
 struct lowpan_nhc** lowpan_nexthdr_nhcs ; 
 int lowpan_nhc_insert (struct lowpan_nhc*) ; 
 int /*<<< orphan*/  lowpan_nhc_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct lowpan_nhc*) ; 

int lowpan_nhc_add(struct lowpan_nhc *nhc)
{
	int ret;

	if (!nhc->idlen || !nhc->idsetup)
		return -EINVAL;

	WARN_ONCE(nhc->idlen > LOWPAN_NHC_MAX_ID_LEN,
		  "LOWPAN_NHC_MAX_ID_LEN should be updated to %zd.\n",
		  nhc->idlen);

	nhc->idsetup(nhc);

	spin_lock_bh(&lowpan_nhc_lock);

	if (lowpan_nexthdr_nhcs[nhc->nexthdr]) {
		ret = -EEXIST;
		goto out;
	}

	ret = lowpan_nhc_insert(nhc);
	if (ret < 0)
		goto out;

	lowpan_nexthdr_nhcs[nhc->nexthdr] = nhc;
out:
	spin_unlock_bh(&lowpan_nhc_lock);
	return ret;
}