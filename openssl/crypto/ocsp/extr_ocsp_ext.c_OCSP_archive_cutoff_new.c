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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_GENERALIZEDTIME_new () ; 
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_set_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NID_id_pkix_OCSP_archiveCutoff ; 
 int /*<<< orphan*/ * X509V3_EXT_i2d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

X509_EXTENSION *OCSP_archive_cutoff_new(char *tim)
{
    X509_EXTENSION *x = NULL;
    ASN1_GENERALIZEDTIME *gt = NULL;

    if ((gt = ASN1_GENERALIZEDTIME_new()) == NULL)
        goto err;
    if (!(ASN1_GENERALIZEDTIME_set_string(gt, tim)))
        goto err;
    x = X509V3_EXT_i2d(NID_id_pkix_OCSP_archiveCutoff, 0, gt);
 err:
    ASN1_GENERALIZEDTIME_free(gt);
    return x;
}