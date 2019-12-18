#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* dhpeer; } ;
typedef  TYPE_1__ PROV_DH_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DH_free (void*) ; 
 int /*<<< orphan*/  DH_up_ref (void*) ; 

__attribute__((used)) static int dh_set_peer(void *vpdhctx, void *vdh)
{
    PROV_DH_CTX *pdhctx = (PROV_DH_CTX *)vpdhctx;

    if (pdhctx == NULL || vdh == NULL || !DH_up_ref(vdh))
        return 0;
    DH_free(pdhctx->dhpeer);
    pdhctx->dhpeer = vdh;
    return 1;
}