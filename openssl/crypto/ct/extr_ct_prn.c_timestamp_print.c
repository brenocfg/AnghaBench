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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  genstr ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_adj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_GENERALIZEDTIME_new () ; 
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ASN1_GENERALIZEDTIME_set_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void timestamp_print(uint64_t timestamp, BIO *out)
{
    ASN1_GENERALIZEDTIME *gen = ASN1_GENERALIZEDTIME_new();
    char genstr[20];

    if (gen == NULL)
        return;
    ASN1_GENERALIZEDTIME_adj(gen, (time_t)0,
                             (int)(timestamp / 86400000),
                             (timestamp % 86400000) / 1000);
    /*
     * Note GeneralizedTime from ASN1_GENERALIZETIME_adj is always 15
     * characters long with a final Z. Update it with fractional seconds.
     */
    BIO_snprintf(genstr, sizeof(genstr), "%.14s.%03dZ",
                 ASN1_STRING_get0_data(gen), (unsigned int)(timestamp % 1000));
    if (ASN1_GENERALIZEDTIME_set_string(gen, genstr))
        ASN1_GENERALIZEDTIME_print(out, gen);
    ASN1_GENERALIZEDTIME_free(gen);
}