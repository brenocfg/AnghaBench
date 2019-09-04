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
typedef  int /*<<< orphan*/  SIGALG_LOOKUP ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 scalar_t__ RSA_PSS_MINIMUM_KEY_SIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ RSA_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tls1_lookup_md (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int rsa_pss_check_min_key_size(const RSA *rsa, const SIGALG_LOOKUP *lu)
{
    const EVP_MD *md;

    if (rsa == NULL)
        return 0;
    if (!tls1_lookup_md(lu, &md) || md == NULL)
        return 0;
    if (RSA_size(rsa) < RSA_PSS_MINIMUM_KEY_SIZE(md))
        return 0;
    return 1;
}