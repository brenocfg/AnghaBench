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
struct TYPE_4__ {int /*<<< orphan*/ * next; void* data; int /*<<< orphan*/  priority; } ;
typedef  TYPE_1__ pitem ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  SSL_F_PITEM_NEW ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 

pitem *pitem_new(unsigned char *prio64be, void *data)
{
    pitem *item = OPENSSL_malloc(sizeof(*item));

    if (item == NULL) {
        SSLerr(SSL_F_PITEM_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    memcpy(item->priority, prio64be, sizeof(item->priority));
    item->data = data;
    item->next = NULL;
    return item;
}