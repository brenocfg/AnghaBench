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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  log_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  logs; } ;
typedef  TYPE_1__ CTLOG_STORE ;
typedef  TYPE_2__ CTLOG ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int sk_CTLOG_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_CTLOG_value (int /*<<< orphan*/ ,int) ; 

const CTLOG *CTLOG_STORE_get0_log_by_id(const CTLOG_STORE *store,
                                        const uint8_t *log_id,
                                        size_t log_id_len)
{
    int i;

    for (i = 0; i < sk_CTLOG_num(store->logs); ++i) {
        const CTLOG *log = sk_CTLOG_value(store->logs, i);
        if (memcmp(log->log_id, log_id, log_id_len) == 0)
            return log;
    }

    return NULL;
}