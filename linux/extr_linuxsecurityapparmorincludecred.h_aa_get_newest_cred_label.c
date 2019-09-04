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
struct cred {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_cred_raw_label (struct cred const*) ; 
 struct aa_label* aa_get_newest_label (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct aa_label *aa_get_newest_cred_label(const struct cred *cred)
{
	return aa_get_newest_label(aa_cred_raw_label(cred));
}