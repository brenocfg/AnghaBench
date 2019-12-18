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
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 scalar_t__ EVP_MD_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ NID_sha1 ; 
 int /*<<< orphan*/ * X509_ALGOR_new () ; 
 int /*<<< orphan*/  X509_ALGOR_set_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int rsa_md_to_algor(X509_ALGOR **palg, const EVP_MD *md)
{
    if (md == NULL || EVP_MD_type(md) == NID_sha1)
        return 1;
    *palg = X509_ALGOR_new();
    if (*palg == NULL)
        return 0;
    X509_ALGOR_set_md(*palg, md);
    return 1;
}