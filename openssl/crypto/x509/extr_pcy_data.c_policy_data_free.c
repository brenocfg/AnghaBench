#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  expected_policy_set; int /*<<< orphan*/  qualifier_set; int /*<<< orphan*/  valid_policy; } ;
typedef  TYPE_1__ X509_POLICY_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  POLICYQUALINFO_free ; 
 int POLICY_DATA_FLAG_SHARED_QUALIFIERS ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sk_POLICYQUALINFO_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void policy_data_free(X509_POLICY_DATA *data)
{
    if (data == NULL)
        return;
    ASN1_OBJECT_free(data->valid_policy);
    /* Don't free qualifiers if shared */
    if (!(data->flags & POLICY_DATA_FLAG_SHARED_QUALIFIERS))
        sk_POLICYQUALINFO_pop_free(data->qualifier_set, POLICYQUALINFO_free);
    sk_ASN1_OBJECT_pop_free(data->expected_policy_set, ASN1_OBJECT_free);
    OPENSSL_free(data);
}