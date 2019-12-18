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
struct TYPE_3__ {int /*<<< orphan*/  name_id; int /*<<< orphan*/ * prov; } ;
typedef  TYPE_1__ EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  evp_names_do_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (char const*,void*),void*) ; 

void EVP_MD_names_do_all(const EVP_MD *md,
                         void (*fn)(const char *name, void *data),
                         void *data)
{
    if (md->prov != NULL)
        evp_names_do_all(md->prov, md->name_id, fn, data);
}