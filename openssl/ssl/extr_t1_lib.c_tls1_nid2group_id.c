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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int nid; int /*<<< orphan*/  group_id; } ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_1__*) ; 
 TYPE_1__* nid_list ; 

__attribute__((used)) static uint16_t tls1_nid2group_id(int nid)
{
    size_t i;

    for (i = 0; i < OSSL_NELEM(nid_list); i++) {
        if (nid_list[i].nid == nid)
            return nid_list[i].group_id;
    }
    return 0;
}