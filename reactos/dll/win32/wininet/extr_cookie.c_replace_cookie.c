#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ cookie_t ;
typedef  int /*<<< orphan*/  cookie_container_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_cookie (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  delete_cookie (TYPE_1__*) ; 
 TYPE_1__* find_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  substrz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void replace_cookie(cookie_container_t *container, cookie_t *new_cookie)
{
    cookie_t *old_cookie;

    old_cookie = find_cookie(container, substrz(new_cookie->name));
    if(old_cookie)
        delete_cookie(old_cookie);

    add_cookie(container, new_cookie);
}