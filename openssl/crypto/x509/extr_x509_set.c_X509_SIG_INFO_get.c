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
typedef  int uint32_t ;
struct TYPE_3__ {int mdnid; int pknid; int secbits; int flags; } ;
typedef  TYPE_1__ X509_SIG_INFO ;

/* Variables and functions */
 int X509_SIG_INFO_VALID ; 

int X509_SIG_INFO_get(const X509_SIG_INFO *siginf, int *mdnid, int *pknid,
                      int *secbits, uint32_t *flags)
{
    if (mdnid != NULL)
        *mdnid = siginf->mdnid;
    if (pknid != NULL)
        *pknid = siginf->pknid;
    if (secbits != NULL)
        *secbits = siginf->secbits;
    if (flags != NULL)
        *flags = siginf->flags;
    return (siginf->flags & X509_SIG_INFO_VALID) != 0;
}