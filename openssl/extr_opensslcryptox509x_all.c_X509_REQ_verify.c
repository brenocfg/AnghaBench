#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  req_info; int /*<<< orphan*/  signature; int /*<<< orphan*/  sig_alg; } ;
typedef  TYPE_1__ X509_REQ ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int ASN1_item_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_REQ_INFO ; 

int X509_REQ_verify(X509_REQ *a, EVP_PKEY *r)
{
    return (ASN1_item_verify(ASN1_ITEM_rptr(X509_REQ_INFO),
                             &a->sig_alg, a->signature, &a->req_info, r));
}