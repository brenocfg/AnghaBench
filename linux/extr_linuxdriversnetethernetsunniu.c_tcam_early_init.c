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
struct niu {int dummy; } ;

/* Variables and functions */
 unsigned long CLASS_CODE_ETHERTYPE1 ; 
 unsigned long CLASS_CODE_ETHERTYPE2 ; 
 unsigned long CLASS_CODE_USER_PROG1 ; 
 unsigned long CLASS_CODE_USER_PROG4 ; 
 int /*<<< orphan*/  DEFAULT_TCAM_ACCESS_RATIO ; 
 int /*<<< orphan*/  DEFAULT_TCAM_LATENCY ; 
 int /*<<< orphan*/  tcam_enable (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcam_set_lat_and_ratio (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tcam_user_eth_class_enable (struct niu*,unsigned long,int /*<<< orphan*/ ) ; 
 int tcam_user_ip_class_enable (struct niu*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcam_early_init(struct niu *np)
{
	unsigned long i;
	int err;

	tcam_enable(np, 0);
	tcam_set_lat_and_ratio(np,
			       DEFAULT_TCAM_LATENCY,
			       DEFAULT_TCAM_ACCESS_RATIO);
	for (i = CLASS_CODE_ETHERTYPE1; i <= CLASS_CODE_ETHERTYPE2; i++) {
		err = tcam_user_eth_class_enable(np, i, 0);
		if (err)
			return err;
	}
	for (i = CLASS_CODE_USER_PROG1; i <= CLASS_CODE_USER_PROG4; i++) {
		err = tcam_user_ip_class_enable(np, i, 0);
		if (err)
			return err;
	}

	return 0;
}