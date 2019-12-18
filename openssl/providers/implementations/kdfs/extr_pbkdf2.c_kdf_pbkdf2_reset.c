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
typedef  int /*<<< orphan*/  KDF_PBKDF2 ;

/* Variables and functions */
 int /*<<< orphan*/  kdf_pbkdf2_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdf_pbkdf2_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kdf_pbkdf2_reset(void *vctx)
{
    KDF_PBKDF2 *ctx = (KDF_PBKDF2 *)vctx;

    kdf_pbkdf2_cleanup(ctx);
    kdf_pbkdf2_init(ctx);
}