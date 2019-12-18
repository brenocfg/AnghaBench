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
 int /*<<< orphan*/  crypto_free_sync_skcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxkad_ci ; 
 int /*<<< orphan*/  rxkad_ci_req ; 
 int /*<<< orphan*/  skcipher_request_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxkad_exit(void)
{
	crypto_free_sync_skcipher(rxkad_ci);
	skcipher_request_free(rxkad_ci_req);
}