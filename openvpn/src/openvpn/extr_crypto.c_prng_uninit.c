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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nonce_data ; 
 int /*<<< orphan*/ * nonce_md ; 
 scalar_t__ nonce_secret_len ; 

void
prng_uninit(void)
{
    free(nonce_data);
    nonce_data = NULL;
    nonce_md = NULL;
    nonce_secret_len = 0;
}