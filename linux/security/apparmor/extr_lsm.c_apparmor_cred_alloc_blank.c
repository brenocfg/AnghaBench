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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  set_cred_label (struct cred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apparmor_cred_alloc_blank(struct cred *cred, gfp_t gfp)
{
	set_cred_label(cred, NULL);
	return 0;
}