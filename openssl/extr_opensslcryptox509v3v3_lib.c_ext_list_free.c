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
struct TYPE_4__ {int ext_flags; } ;
typedef  TYPE_1__ X509V3_EXT_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int X509V3_EXT_DYNAMIC ; 

__attribute__((used)) static void ext_list_free(X509V3_EXT_METHOD *ext)
{
    if (ext->ext_flags & X509V3_EXT_DYNAMIC)
        OPENSSL_free(ext);
}