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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_get_int64 (scalar_t__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_R_INVALID_NUMBER ; 
 int /*<<< orphan*/  ASN1_R_TOO_LARGE ; 
 int /*<<< orphan*/  ASN1_R_TOO_SMALL ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 

__attribute__((used)) static int crmf_asn1_get_int(const ASN1_INTEGER *a)
{
    int64_t res;

    if (!ASN1_INTEGER_get_int64(&res, a)) {
        CRMFerr(0, ASN1_R_INVALID_NUMBER);
        return -1;
    }
    if (res < INT_MIN) {
        CRMFerr(0, ASN1_R_TOO_SMALL);
        return -1;
    }
    if (res > INT_MAX) {
        CRMFerr(0, ASN1_R_TOO_LARGE);
        return -1;
    }
    return (int)res;
}