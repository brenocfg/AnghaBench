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
struct svc_fh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_NORMAL ; 
 int /*<<< orphan*/  fh_lock_nested (struct svc_fh*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fh_lock(struct svc_fh *fhp)
{
	fh_lock_nested(fhp, I_MUTEX_NORMAL);
}