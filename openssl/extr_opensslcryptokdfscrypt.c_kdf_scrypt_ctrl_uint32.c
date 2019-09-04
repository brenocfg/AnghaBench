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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  EVP_KDF_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  KDF_F_KDF_SCRYPT_CTRL_UINT32 ; 
 int /*<<< orphan*/  KDF_R_VALUE_ERROR ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT32_MAX ; 
 int atoi (char const*) ; 
 int call_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdf_scrypt_ctrl ; 

__attribute__((used)) static int kdf_scrypt_ctrl_uint32(EVP_KDF_IMPL *impl, int cmd,
                                  const char *value)
{
    int int_value = atoi(value);

    if (int_value < 0 || (uint64_t)int_value > UINT32_MAX) {
        KDFerr(KDF_F_KDF_SCRYPT_CTRL_UINT32, KDF_R_VALUE_ERROR);
        return 0;
    }
    return call_ctrl(kdf_scrypt_ctrl, impl, cmd, (uint32_t)int_value);
}