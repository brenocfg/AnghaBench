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
struct TYPE_3__ {unsigned char* log_id; size_t log_id_len; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */

size_t SCT_get0_log_id(const SCT *sct, unsigned char **log_id)
{
    *log_id = sct->log_id;
    return sct->log_id_len;
}