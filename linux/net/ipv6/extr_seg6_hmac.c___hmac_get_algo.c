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
typedef  scalar_t__ u8 ;
struct seg6_hmac_algo {scalar_t__ alg_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct seg6_hmac_algo*) ; 
 struct seg6_hmac_algo* hmac_algos ; 

__attribute__((used)) static struct seg6_hmac_algo *__hmac_get_algo(u8 alg_id)
{
	struct seg6_hmac_algo *algo;
	int i, alg_count;

	alg_count = ARRAY_SIZE(hmac_algos);
	for (i = 0; i < alg_count; i++) {
		algo = &hmac_algos[i];
		if (algo->alg_id == alg_id)
			return algo;
	}

	return NULL;
}