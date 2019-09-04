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

/* Variables and functions */

__attribute__((used)) static inline void alter_cred_subscribers(const struct cred *_cred, int n)
{
#ifdef CONFIG_DEBUG_CREDENTIALS
	struct cred *cred = (struct cred *) _cred;

	atomic_add(n, &cred->subscribers);
#endif
}