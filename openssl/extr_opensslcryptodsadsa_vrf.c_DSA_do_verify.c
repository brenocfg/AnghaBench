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
struct TYPE_6__ {TYPE_1__* meth; } ;
struct TYPE_5__ {int (* dsa_do_verify ) (unsigned char const*,int,int /*<<< orphan*/ *,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  DSA_SIG ;
typedef  TYPE_2__ DSA ;

/* Variables and functions */
 int stub1 (unsigned char const*,int,int /*<<< orphan*/ *,TYPE_2__*) ; 

int DSA_do_verify(const unsigned char *dgst, int dgst_len, DSA_SIG *sig,
                  DSA *dsa)
{
    return dsa->meth->dsa_do_verify(dgst, dgst_len, sig, dsa);
}