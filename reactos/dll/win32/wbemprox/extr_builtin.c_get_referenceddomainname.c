#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {TYPE_2__* Domains; } ;
struct TYPE_5__ {int /*<<< orphan*/  Buffer; } ;
struct TYPE_6__ {TYPE_1__ Name; } ;
typedef  TYPE_3__ LSA_REFERENCED_DOMAIN_LIST ;

/* Variables and functions */
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *get_referenceddomainname( LSA_REFERENCED_DOMAIN_LIST *domain )
{
    if (!domain || !domain->Domains || !domain->Domains->Name.Buffer) return NULL;
    return heap_strdupW( domain->Domains->Name.Buffer );
}