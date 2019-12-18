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
struct gss_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gss_cred*) ; 

__attribute__((used)) static void
gss_free_cred(struct gss_cred *gss_cred)
{
	kfree(gss_cred);
}