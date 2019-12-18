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
struct TYPE_4__ {int /*<<< orphan*/  name_id; int /*<<< orphan*/ * prov; } ;
typedef  TYPE_1__ EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_nid (TYPE_1__ const*) ; 
 char const* OBJ_nid2sn (int /*<<< orphan*/ ) ; 
 char const* evp_first_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const char *EVP_MD_name(const EVP_MD *md)
{
    if (md->prov != NULL)
        return evp_first_name(md->prov, md->name_id);
#ifndef FIPS_MODE
    return OBJ_nid2sn(EVP_MD_nid(md));
#else
    return NULL;
#endif
}