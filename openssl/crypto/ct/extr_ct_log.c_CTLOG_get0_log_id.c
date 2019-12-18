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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * log_id; } ;
typedef  TYPE_1__ CTLOG ;

/* Variables and functions */
 size_t CT_V1_HASHLEN ; 

void CTLOG_get0_log_id(const CTLOG *log, const uint8_t **log_id,
                       size_t *log_id_len)
{
    *log_id = log->log_id;
    *log_id_len = CT_V1_HASHLEN;
}