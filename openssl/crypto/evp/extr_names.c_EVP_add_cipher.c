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
struct TYPE_3__ {int /*<<< orphan*/  nid; } ;
typedef  TYPE_1__ EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_NAME_TYPE_CIPHER_METH ; 
 int OBJ_NAME_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  OBJ_nid2ln (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_nid2sn (int /*<<< orphan*/ ) ; 

int EVP_add_cipher(const EVP_CIPHER *c)
{
    int r;

    if (c == NULL)
        return 0;

    r = OBJ_NAME_add(OBJ_nid2sn(c->nid), OBJ_NAME_TYPE_CIPHER_METH,
                     (const char *)c);
    if (r == 0)
        return 0;
    r = OBJ_NAME_add(OBJ_nid2ln(c->nid), OBJ_NAME_TYPE_CIPHER_METH,
                     (const char *)c);
    return r;
}