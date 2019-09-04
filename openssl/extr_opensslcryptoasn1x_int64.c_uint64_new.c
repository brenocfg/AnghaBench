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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_UINT64_NEW ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ OPENSSL_zalloc (int) ; 

__attribute__((used)) static int uint64_new(ASN1_VALUE **pval, const ASN1_ITEM *it)
{
    if ((*pval = (ASN1_VALUE *)OPENSSL_zalloc(sizeof(uint64_t))) == NULL) {
        ASN1err(ASN1_F_UINT64_NEW, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    return 1;
}