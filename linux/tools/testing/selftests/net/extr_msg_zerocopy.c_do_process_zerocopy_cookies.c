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
typedef  int uint32_t ;
struct rds_zcopy_cookies {int num; int* cookies; } ;

/* Variables and functions */
 int RDS_MAX_ZCOOKIES ; 
 int cfg_verbose ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static uint32_t do_process_zerocopy_cookies(struct rds_zcopy_cookies *ck)
{
	int i;

	if (ck->num > RDS_MAX_ZCOOKIES)
		error(1, 0, "Returned %d cookies, max expected %d\n",
		      ck->num, RDS_MAX_ZCOOKIES);
	for (i = 0; i < ck->num; i++)
		if (cfg_verbose >= 2)
			fprintf(stderr, "%d\n", ck->cookies[i]);
	return ck->num;
}