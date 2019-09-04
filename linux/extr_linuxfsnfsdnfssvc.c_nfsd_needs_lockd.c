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

/* Variables and functions */
 int /*<<< orphan*/ ** nfsd_versions ; 

__attribute__((used)) static bool nfsd_needs_lockd(void)
{
#if defined(CONFIG_NFSD_V3)
	return (nfsd_versions[2] != NULL) || (nfsd_versions[3] != NULL);
#else
	return (nfsd_versions[2] != NULL);
#endif
}