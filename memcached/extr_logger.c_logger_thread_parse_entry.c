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
struct logger_stats {int dummy; } ;
struct TYPE_8__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_9__ {int event; TYPE_1__ tv; scalar_t__ data; scalar_t__ gid; } ;
typedef  TYPE_2__ logentry ;
typedef  enum logger_parse_entry_ret { ____Placeholder_logger_parse_entry_ret } logger_parse_entry_ret ;

/* Variables and functions */
#define  LOGGER_EVICTION_ENTRY 132 
#define  LOGGER_EXT_WRITE_ENTRY 131 
#define  LOGGER_ITEM_GET_ENTRY 130 
#define  LOGGER_ITEM_STORE_ENTRY 129 
 int LOGGER_PARSE_ENTRY_FAILED ; 
 int LOGGER_PARSE_ENTRY_OK ; 
 int LOGGER_PARSE_SCRATCH ; 
#define  LOGGER_TEXT_ENTRY 128 
 int /*<<< orphan*/  L_DEBUG (char*) ; 
 int _logger_thread_parse_ee (TYPE_2__*,char*) ; 
 int _logger_thread_parse_extw (TYPE_2__*,char*) ; 
 int _logger_thread_parse_ige (TYPE_2__*,char*) ; 
 int _logger_thread_parse_ise (TYPE_2__*,char*) ; 
 int snprintf (char*,int,char*,int,int,unsigned long long,char*) ; 

__attribute__((used)) static enum logger_parse_entry_ret logger_thread_parse_entry(logentry *e, struct logger_stats *ls,
        char *scratch, int *scratch_len) {
    int total = 0;

    switch (e->event) {
        case LOGGER_TEXT_ENTRY:
            total = snprintf(scratch, LOGGER_PARSE_SCRATCH, "ts=%d.%d gid=%llu %s\n",
                        (int)e->tv.tv_sec, (int)e->tv.tv_usec,
                        (unsigned long long) e->gid, (char *) e->data);
            break;
        case LOGGER_EVICTION_ENTRY:
            total = _logger_thread_parse_ee(e, scratch);
            break;
#ifdef EXTSTORE
        case LOGGER_EXT_WRITE_ENTRY:
            total = _logger_thread_parse_extw(e, scratch);
            break;
#endif
        case LOGGER_ITEM_GET_ENTRY:
            total = _logger_thread_parse_ige(e, scratch);
            break;
        case LOGGER_ITEM_STORE_ENTRY:
            total = _logger_thread_parse_ise(e, scratch);
            break;

    }

    if (total >= LOGGER_PARSE_SCRATCH || total <= 0) {
        L_DEBUG("LOGGER: Failed to flatten log entry!\n");
        return LOGGER_PARSE_ENTRY_FAILED;
    } else {
        *scratch_len = total;
    }

    return LOGGER_PARSE_ENTRY_OK;
}