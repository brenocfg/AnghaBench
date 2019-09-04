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
struct knfsd_fh {int /*<<< orphan*/  fh_size; int /*<<< orphan*/  fh_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fh_copy_shallow(struct knfsd_fh *dst, struct knfsd_fh *src)
{
	dst->fh_size = src->fh_size;
	memcpy(&dst->fh_base, &src->fh_base, src->fh_size);
}