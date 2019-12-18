#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* akid; } ;
typedef  TYPE_2__ X509 ;
struct TYPE_5__ {int /*<<< orphan*/  const* keyid; } ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  X509_check_purpose (TYPE_2__*,int,int) ; 

const ASN1_OCTET_STRING *X509_get0_authority_key_id(X509 *x)
{
    /* Call for side-effect of computing hash and caching extensions */
    X509_check_purpose(x, -1, -1);
    return (x->akid != NULL ? x->akid->keyid : NULL);
}