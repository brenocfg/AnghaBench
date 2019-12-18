#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct env_set {struct env_item* list; } ;
struct env_item {scalar_t__ string; struct env_item* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  env_set_del (struct env_set*,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,scalar_t__,int /*<<< orphan*/ ) ; 

void
tls_x509_clear_env(struct env_set *es)
{
    struct env_item *item = es->list;
    while (item)
    {
        struct env_item *next = item->next;
        if (item->string
            && 0 == strncmp("X509_", item->string, strlen("X509_")))
        {
            env_set_del(es, item->string);
        }
        item = next;
    }
}