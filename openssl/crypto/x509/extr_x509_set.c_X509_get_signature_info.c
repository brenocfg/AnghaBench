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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  siginf; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int X509_SIG_INFO_get (int /*<<< orphan*/ *,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_check_purpose (TYPE_1__*,int,int) ; 

int X509_get_signature_info(X509 *x, int *mdnid, int *pknid, int *secbits,
                            uint32_t *flags)
{
    X509_check_purpose(x, -1, -1);
    return X509_SIG_INFO_get(&x->siginf, mdnid, pknid, secbits, flags);
}