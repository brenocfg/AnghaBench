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
typedef  int /*<<< orphan*/  X509_REQ ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int common_verify_sm2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int x509_req_verify_sm2(X509_REQ *x, EVP_PKEY *pkey,
                               int mdnid, int pknid)
{
    return common_verify_sm2(x, pkey, mdnid, pknid, 1);
}