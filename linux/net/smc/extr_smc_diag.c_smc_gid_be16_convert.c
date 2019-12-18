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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void smc_gid_be16_convert(__u8 *buf, u8 *gid_raw)
{
	sprintf(buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
		be16_to_cpu(((__be16 *)gid_raw)[0]),
		be16_to_cpu(((__be16 *)gid_raw)[1]),
		be16_to_cpu(((__be16 *)gid_raw)[2]),
		be16_to_cpu(((__be16 *)gid_raw)[3]),
		be16_to_cpu(((__be16 *)gid_raw)[4]),
		be16_to_cpu(((__be16 *)gid_raw)[5]),
		be16_to_cpu(((__be16 *)gid_raw)[6]),
		be16_to_cpu(((__be16 *)gid_raw)[7]));
}