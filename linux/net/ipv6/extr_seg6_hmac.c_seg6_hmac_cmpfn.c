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
struct seg6_hmac_info {scalar_t__ hmackeyid; } ;
struct rhashtable_compare_arg {scalar_t__ key; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */

__attribute__((used)) static int seg6_hmac_cmpfn(struct rhashtable_compare_arg *arg, const void *obj)
{
	const struct seg6_hmac_info *hinfo = obj;

	return (hinfo->hmackeyid != *(__u32 *)arg->key);
}