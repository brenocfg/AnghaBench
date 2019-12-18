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
struct TYPE_5__ {int /*<<< orphan*/  const* keybag; } ;
struct TYPE_6__ {TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_2__ PKCS12_SAFEBAG ;

/* Variables and functions */
 scalar_t__ NID_keyBag ; 
 scalar_t__ PKCS12_SAFEBAG_get_nid (TYPE_2__ const*) ; 

const PKCS8_PRIV_KEY_INFO *PKCS12_SAFEBAG_get0_p8inf(const PKCS12_SAFEBAG *bag)
{
    if (PKCS12_SAFEBAG_get_nid(bag) != NID_keyBag)
        return NULL;
    return bag->value.keybag;
}