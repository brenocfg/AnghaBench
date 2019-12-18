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
struct timespec64 {int dummy; } ;
struct audit_context {int dummy; } ;

/* Variables and functions */
 unsigned int audit_serial () ; 
 int /*<<< orphan*/  auditsc_get_stamp (struct audit_context*,struct timespec64*,unsigned int*) ; 
 int /*<<< orphan*/  ktime_get_coarse_real_ts64 (struct timespec64*) ; 

__attribute__((used)) static inline void audit_get_stamp(struct audit_context *ctx,
				   struct timespec64 *t, unsigned int *serial)
{
	if (!ctx || !auditsc_get_stamp(ctx, t, serial)) {
		ktime_get_coarse_real_ts64(t);
		*serial = audit_serial();
	}
}