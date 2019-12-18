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
typedef  int /*<<< orphan*/  BLAKE2B_PARAM ;
typedef  int /*<<< orphan*/  BLAKE2B_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  blake2b_init_param (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int blake2b_init(BLAKE2B_CTX *c, const BLAKE2B_PARAM *P)
{
    blake2b_init_param(c, P);
    return 1;
}