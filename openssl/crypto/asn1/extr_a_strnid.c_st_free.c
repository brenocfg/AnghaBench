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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ ASN1_STRING_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int STABLE_FLAGS_MALLOC ; 

__attribute__((used)) static void st_free(ASN1_STRING_TABLE *tbl)
{
    if (tbl->flags & STABLE_FLAGS_MALLOC)
        OPENSSL_free(tbl);
}