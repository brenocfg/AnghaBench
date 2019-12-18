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
struct TYPE_3__ {int /*<<< orphan*/  attributes; } ;
typedef  TYPE_1__ EVP_PKEY ;

/* Variables and functions */
 int X509at_get_attr_by_NID (int /*<<< orphan*/ ,int,int) ; 

int EVP_PKEY_get_attr_by_NID(const EVP_PKEY *key, int nid, int lastpos)
{
    return X509at_get_attr_by_NID(key->attributes, nid, lastpos);
}