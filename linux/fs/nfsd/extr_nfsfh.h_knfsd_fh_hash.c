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
typedef  int /*<<< orphan*/  u32 ;
struct knfsd_fh {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u32
knfsd_fh_hash(struct knfsd_fh *fh)
{
	return 0;
}