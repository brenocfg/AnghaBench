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
typedef  int /*<<< orphan*/  const ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  const* ASN1_STRING_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_TIME_free (int /*<<< orphan*/  const*) ; 

int x509_set1_time(ASN1_TIME **ptm, const ASN1_TIME *tm)
{
    ASN1_TIME *in;
    in = *ptm;
    if (in != tm) {
        in = ASN1_STRING_dup(tm);
        if (in != NULL) {
            ASN1_TIME_free(*ptm);
            *ptm = in;
        }
    }
    return (in != NULL);
}