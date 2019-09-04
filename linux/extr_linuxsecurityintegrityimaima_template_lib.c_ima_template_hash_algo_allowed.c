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

/* Variables and functions */
 scalar_t__ HASH_ALGO_MD5 ; 
 scalar_t__ HASH_ALGO_SHA1 ; 

__attribute__((used)) static bool ima_template_hash_algo_allowed(u8 algo)
{
	if (algo == HASH_ALGO_SHA1 || algo == HASH_ALGO_MD5)
		return true;

	return false;
}