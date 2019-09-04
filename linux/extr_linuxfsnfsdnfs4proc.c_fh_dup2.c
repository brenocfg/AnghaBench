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
struct svc_fh {scalar_t__ fh_export; int /*<<< orphan*/  fh_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exp_get (scalar_t__) ; 
 int /*<<< orphan*/  fh_put (struct svc_fh*) ; 

__attribute__((used)) static inline void
fh_dup2(struct svc_fh *dst, struct svc_fh *src)
{
	fh_put(dst);
	dget(src->fh_dentry);
	if (src->fh_export)
		exp_get(src->fh_export);
	*dst = *src;
}