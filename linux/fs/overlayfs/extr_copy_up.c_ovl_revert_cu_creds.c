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
struct ovl_cu_creds {scalar_t__ new; int /*<<< orphan*/  old; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_cred (scalar_t__) ; 
 int /*<<< orphan*/  revert_creds (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ovl_revert_cu_creds(struct ovl_cu_creds *cc)
{
	if (cc->new) {
		revert_creds(cc->old);
		put_cred(cc->new);
	}
}