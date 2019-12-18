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
typedef  int /*<<< orphan*/  RAND_DRBG ;
typedef  int /*<<< orphan*/  HOOK_CTX ;

/* Variables and functions */
 scalar_t__ RAND_DRBG_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_data_index ; 

__attribute__((used)) static HOOK_CTX *get_hook_ctx(RAND_DRBG *drbg)
{
    return (HOOK_CTX *)RAND_DRBG_get_ex_data(drbg, app_data_index);
}