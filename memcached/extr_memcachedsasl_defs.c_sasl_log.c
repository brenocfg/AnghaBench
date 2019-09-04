#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int verbose; } ;

/* Variables and functions */
#define  SASL_LOG_DEBUG 134 
#define  SASL_LOG_FAIL 133 
#define  SASL_LOG_NONE 132 
#define  SASL_LOG_NOTE 131 
#define  SASL_LOG_PASS 130 
#define  SASL_LOG_TRACE 129 
#define  SASL_LOG_WARN 128 
 int SASL_OK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*) ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int sasl_log(void *context, int level, const char *message)
{
    bool log = true;

    switch (level) {
    case SASL_LOG_NONE:
        log = false;
        break;
    case SASL_LOG_PASS:
    case SASL_LOG_TRACE:
    case SASL_LOG_DEBUG:
    case SASL_LOG_NOTE:
        if (settings.verbose < 2) {
            log = false;
        }
        break;
    case SASL_LOG_WARN:
    case SASL_LOG_FAIL:
        if (settings.verbose < 1) {
            log = false;
        }
        break;
    default:
        /* This is an error */
        ;
    }

    if (log) {
        fprintf(stderr, "SASL (severity %d): %s\n", level, message);
    }

    return SASL_OK;
}