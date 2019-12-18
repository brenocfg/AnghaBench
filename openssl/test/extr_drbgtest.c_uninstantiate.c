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

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int RAND_DRBG_uninstantiate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uninstantiate(RAND_DRBG *drbg)
{
    int ret = drbg == NULL ? 1 : RAND_DRBG_uninstantiate(drbg);

    ERR_clear_error();
    return ret;
}