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
struct TYPE_4__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_cookie (TYPE_1__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_cookie( cookie_t *cookie )
{
    list_remove( &cookie->entry );
    free_cookie( cookie );
}