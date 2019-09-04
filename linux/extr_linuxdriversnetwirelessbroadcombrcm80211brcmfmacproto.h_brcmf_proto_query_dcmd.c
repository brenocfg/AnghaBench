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
typedef  int /*<<< orphan*/  uint ;
struct brcmf_pub {TYPE_1__* proto; } ;
struct TYPE_2__ {int (* query_dcmd ) (struct brcmf_pub*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int stub1 (struct brcmf_pub*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int brcmf_proto_query_dcmd(struct brcmf_pub *drvr, int ifidx,
					 uint cmd, void *buf, uint len,
					 int *fwerr)
{
	return drvr->proto->query_dcmd(drvr, ifidx, cmd, buf, len,fwerr);
}