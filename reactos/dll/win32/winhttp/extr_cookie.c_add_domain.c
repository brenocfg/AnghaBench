#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cookie_cache; } ;
typedef  TYPE_1__ session_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  entry; int /*<<< orphan*/  cookies; } ;
typedef  TYPE_2__ domain_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static domain_t *add_domain( session_t *session, WCHAR *name )
{
    domain_t *domain;

    if (!(domain = heap_alloc_zero( sizeof(domain_t) ))) return NULL;

    list_init( &domain->entry );
    list_init( &domain->cookies );

    domain->name = strdupW( name );
    list_add_tail( &session->cookie_cache, &domain->entry );

    TRACE("%s\n", debugstr_w(domain->name));
    return domain;
}