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
struct TYPE_6__ {int /*<<< orphan*/ * data; TYPE_1__* meth; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* copy ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EVP_MAC_IMPL ;
typedef  TYPE_2__ EVP_MAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int EVP_MAC_CTX_copy(EVP_MAC_CTX *dst, const EVP_MAC_CTX *src)
{
    EVP_MAC_IMPL *macdata;

    if (src->data != NULL && !dst->meth->copy(dst->data, src->data))
        return 0;

    macdata = dst->data;
    *dst = *src;
    dst->data = macdata;

    return 1;
}