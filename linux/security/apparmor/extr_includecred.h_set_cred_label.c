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
struct cred {struct aa_label** security; } ;
struct aa_label {int dummy; } ;
struct TYPE_2__ {int lbs_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 TYPE_1__ apparmor_blob_sizes ; 

__attribute__((used)) static inline void set_cred_label(const struct cred *cred,
				  struct aa_label *label)
{
	struct aa_label **blob = cred->security + apparmor_blob_sizes.lbs_cred;

	AA_BUG(!blob);
	*blob = label;
}