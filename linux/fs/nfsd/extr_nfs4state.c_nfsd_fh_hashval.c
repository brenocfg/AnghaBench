#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fh_pad; } ;
struct knfsd_fh {int /*<<< orphan*/  fh_size; TYPE_1__ fh_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_QUADLEN (int /*<<< orphan*/ ) ; 
 unsigned int jhash2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int nfsd_fh_hashval(struct knfsd_fh *fh)
{
	return jhash2(fh->fh_base.fh_pad, XDR_QUADLEN(fh->fh_size), 0);
}