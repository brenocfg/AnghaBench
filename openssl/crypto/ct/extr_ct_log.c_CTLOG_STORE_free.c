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
struct TYPE_4__ {int /*<<< orphan*/  logs; } ;
typedef  TYPE_1__ CTLOG_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  CTLOG_free ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sk_CTLOG_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CTLOG_STORE_free(CTLOG_STORE *store)
{
    if (store != NULL) {
        sk_CTLOG_pop_free(store->logs, CTLOG_free);
        OPENSSL_free(store);
    }
}