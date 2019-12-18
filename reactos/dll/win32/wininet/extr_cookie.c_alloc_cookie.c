#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ substr_t ;
struct TYPE_9__ {void* data; void* name; int /*<<< orphan*/  entry; int /*<<< orphan*/  flags; void* create; void* expiry; } ;
typedef  TYPE_2__ cookie_t ;
typedef  void* FILETIME ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  delete_cookie (TYPE_2__*) ; 
 TYPE_2__* heap_alloc (int) ; 
 void* heap_strndupW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static cookie_t *alloc_cookie(substr_t name, substr_t data, FILETIME expiry, FILETIME create_time, DWORD flags)
{
    cookie_t *new_cookie;

    new_cookie = heap_alloc(sizeof(*new_cookie));
    if(!new_cookie)
        return NULL;

    new_cookie->expiry = expiry;
    new_cookie->create = create_time;
    new_cookie->flags = flags;
    list_init(&new_cookie->entry);

    new_cookie->name = heap_strndupW(name.str, name.len);
    new_cookie->data = heap_strndupW(data.str, data.len);
    if(!new_cookie->name || !new_cookie->data) {
        delete_cookie(new_cookie);
        return NULL;
    }

    return new_cookie;
}