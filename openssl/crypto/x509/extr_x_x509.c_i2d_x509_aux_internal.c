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
struct TYPE_4__ {int /*<<< orphan*/  aux; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int i2d_X509 (TYPE_1__ const*,unsigned char**) ; 
 int i2d_X509_CERT_AUX (int /*<<< orphan*/ ,unsigned char**) ; 

__attribute__((used)) static int i2d_x509_aux_internal(const X509 *a, unsigned char **pp)
{
    int length, tmplen;
    unsigned char *start = pp != NULL ? *pp : NULL;

    /*
     * This might perturb *pp on error, but fixing that belongs in i2d_X509()
     * not here.  It should be that if a == NULL length is zero, but we check
     * both just in case.
     */
    length = i2d_X509(a, pp);
    if (length <= 0 || a == NULL)
        return length;

    tmplen = i2d_X509_CERT_AUX(a->aux, pp);
    if (tmplen < 0) {
        if (start != NULL)
            *pp = start;
        return tmplen;
    }
    length += tmplen;

    return length;
}