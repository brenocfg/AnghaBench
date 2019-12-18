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
struct TYPE_4__ {int /*<<< orphan*/  t; int /*<<< orphan*/  d; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ RSA_PRIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsa_multip_info_free_ex (TYPE_1__*) ; 

void rsa_multip_info_free(RSA_PRIME_INFO *pinfo)
{
    /* free a RSA_PRIME_INFO structure */
    BN_clear_free(pinfo->r);
    BN_clear_free(pinfo->d);
    BN_clear_free(pinfo->t);
    rsa_multip_info_free_ex(pinfo);
}