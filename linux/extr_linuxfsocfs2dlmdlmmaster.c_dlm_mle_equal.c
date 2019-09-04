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
struct dlm_master_list_entry {unsigned int mnamelen; int /*<<< orphan*/  mname; struct dlm_ctxt* dlm; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int dlm_mle_equal(struct dlm_ctxt *dlm,
				struct dlm_master_list_entry *mle,
				const char *name,
				unsigned int namelen)
{
	if (dlm != mle->dlm)
		return 0;

	if (namelen != mle->mnamelen ||
	    memcmp(name, mle->mname, namelen) != 0)
		return 0;

	return 1;
}