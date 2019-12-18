#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* bag; } ;
struct TYPE_8__ {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ PKCS12_SAFEBAG ;

/* Variables and functions */
 int NID_certBag ; 
 int NID_crlBag ; 
 int NID_secretBag ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int PKCS12_SAFEBAG_get_nid (TYPE_3__ const*) ; 

int PKCS12_SAFEBAG_get_bag_nid(const PKCS12_SAFEBAG *bag)
{
    int btype = PKCS12_SAFEBAG_get_nid(bag);

    if (btype != NID_certBag && btype != NID_crlBag && btype != NID_secretBag)
        return -1;
    return OBJ_obj2nid(bag->value.bag->type);
}