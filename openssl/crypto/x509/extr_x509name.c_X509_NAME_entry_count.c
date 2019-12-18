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
struct TYPE_3__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ X509_NAME ;

/* Variables and functions */
 int sk_X509_NAME_ENTRY_num (int /*<<< orphan*/ ) ; 

int X509_NAME_entry_count(const X509_NAME *name)
{
    if (name == NULL)
        return 0;
    return sk_X509_NAME_ENTRY_num(name->entries);
}