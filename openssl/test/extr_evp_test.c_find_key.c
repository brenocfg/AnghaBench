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
struct TYPE_3__ {int /*<<< orphan*/ * key; int /*<<< orphan*/  name; struct TYPE_3__* next; } ;
typedef  TYPE_1__ KEY_LIST ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int find_key(EVP_PKEY **ppk, const char *name, KEY_LIST *lst)
{
    for (; lst != NULL; lst = lst->next) {
        if (strcmp(lst->name, name) == 0) {
            if (ppk != NULL)
                *ppk = lst->key;
            return 1;
        }
    }
    return 0;
}