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
struct TYPE_2__ {int /*<<< orphan*/ * pub; scalar_t__* prv; } ;
struct sockaddr_atmsvc {TYPE_1__ sas_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_ESA_LEN ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int identical(const struct sockaddr_atmsvc *a, const struct sockaddr_atmsvc *b)
{
	if (*a->sas_addr.prv)
		if (memcmp(a->sas_addr.prv, b->sas_addr.prv, ATM_ESA_LEN))
			return 0;
	if (!*a->sas_addr.pub)
		return !*b->sas_addr.pub;
	if (!*b->sas_addr.pub)
		return 0;
	return !strcmp(a->sas_addr.pub, b->sas_addr.pub);
}