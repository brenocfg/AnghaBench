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
struct TYPE_4__ {struct TYPE_4__* name; int /*<<< orphan*/  key; struct TYPE_4__* next; } ;
typedef  TYPE_1__ KEY_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void free_key_list(KEY_LIST *lst)
{
    while (lst != NULL) {
        KEY_LIST *next = lst->next;

        EVP_PKEY_free(lst->key);
        OPENSSL_free(lst->name);
        OPENSSL_free(lst);
        lst = next;
    }
}