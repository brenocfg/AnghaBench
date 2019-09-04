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
struct gss_auth {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  gss_free_callback ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gss_put_auth(struct gss_auth *gss_auth)
{
	kref_put(&gss_auth->kref, gss_free_callback);
}