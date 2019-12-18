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
struct TYPE_3__ {scalar_t__ stored; } ;
typedef  TYPE_1__ OSSL_NAMEMAP ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_namemap_free (TYPE_1__*) ; 

__attribute__((used)) static void stored_namemap_free(void *vnamemap)
{
    OSSL_NAMEMAP *namemap = vnamemap;

    /* Pretend it isn't stored, or ossl_namemap_free() will do nothing */
    namemap->stored = 0;
    ossl_namemap_free(namemap);
}