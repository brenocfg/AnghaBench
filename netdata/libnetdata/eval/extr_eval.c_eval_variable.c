#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ calculated_number ;
struct TYPE_6__ {int /*<<< orphan*/  error_msg; scalar_t__ rrdcalc; scalar_t__* status; scalar_t__* before; scalar_t__* after; scalar_t__* this; } ;
struct TYPE_5__ {scalar_t__ hash; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ EVAL_VARIABLE ;
typedef  TYPE_2__ EVAL_EXPRESSION ;

/* Variables and functions */
 int EVAL_ERROR_UNKNOWN_VARIABLE ; 
 scalar_t__ NAN ; 
 scalar_t__ RRDCALC_STATUS_CLEAR ; 
 scalar_t__ RRDCALC_STATUS_CRITICAL ; 
 scalar_t__ RRDCALC_STATUS_REMOVED ; 
 scalar_t__ RRDCALC_STATUS_UNDEFINED ; 
 scalar_t__ RRDCALC_STATUS_UNINITIALIZED ; 
 scalar_t__ RRDCALC_STATUS_WARNING ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ health_variable_lookup (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ now_realtime_sec () ; 
 int /*<<< orphan*/  print_parsed_as_constant (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ simple_hash (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline calculated_number eval_variable(EVAL_EXPRESSION *exp, EVAL_VARIABLE *v, int *error) {
    static uint32_t this_hash = 0, now_hash = 0, after_hash = 0, before_hash = 0, status_hash = 0, removed_hash = 0, uninitialized_hash = 0, undefined_hash = 0, clear_hash = 0, warning_hash = 0, critical_hash = 0;
    calculated_number n;

    if(unlikely(this_hash == 0)) {
        this_hash = simple_hash("this");
        now_hash = simple_hash("now");
        after_hash = simple_hash("after");
        before_hash = simple_hash("before");
        status_hash = simple_hash("status");
        removed_hash = simple_hash("REMOVED");
        uninitialized_hash = simple_hash("UNINITIALIZED");
        undefined_hash = simple_hash("UNDEFINED");
        clear_hash = simple_hash("CLEAR");
        warning_hash = simple_hash("WARNING");
        critical_hash = simple_hash("CRITICAL");
    }

    if(unlikely(v->hash == this_hash && !strcmp(v->name, "this"))) {
        n = (exp->this)?*exp->this:NAN;
        buffer_strcat(exp->error_msg, "[ $this = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == after_hash && !strcmp(v->name, "after"))) {
        n = (exp->after && *exp->after)?*exp->after:NAN;
        buffer_strcat(exp->error_msg, "[ $after = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == before_hash && !strcmp(v->name, "before"))) {
        n = (exp->before && *exp->before)?*exp->before:NAN;
        buffer_strcat(exp->error_msg, "[ $before = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == now_hash && !strcmp(v->name, "now"))) {
        n = now_realtime_sec();
        buffer_strcat(exp->error_msg, "[ $now = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == status_hash && !strcmp(v->name, "status"))) {
        n = (exp->status)?*exp->status:RRDCALC_STATUS_UNINITIALIZED;
        buffer_strcat(exp->error_msg, "[ $status = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == removed_hash && !strcmp(v->name, "REMOVED"))) {
        n = RRDCALC_STATUS_REMOVED;
        buffer_strcat(exp->error_msg, "[ $REMOVED = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == uninitialized_hash && !strcmp(v->name, "UNINITIALIZED"))) {
        n = RRDCALC_STATUS_UNINITIALIZED;
        buffer_strcat(exp->error_msg, "[ $UNINITIALIZED = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == undefined_hash && !strcmp(v->name, "UNDEFINED"))) {
        n = RRDCALC_STATUS_UNDEFINED;
        buffer_strcat(exp->error_msg, "[ $UNDEFINED = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == clear_hash && !strcmp(v->name, "CLEAR"))) {
        n = RRDCALC_STATUS_CLEAR;
        buffer_strcat(exp->error_msg, "[ $CLEAR = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == warning_hash && !strcmp(v->name, "WARNING"))) {
        n = RRDCALC_STATUS_WARNING;
        buffer_strcat(exp->error_msg, "[ $WARNING = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(unlikely(v->hash == critical_hash && !strcmp(v->name, "CRITICAL"))) {
        n = RRDCALC_STATUS_CRITICAL;
        buffer_strcat(exp->error_msg, "[ $CRITICAL = ");
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    if(exp->rrdcalc && health_variable_lookup(v->name, v->hash, exp->rrdcalc, &n)) {
        buffer_sprintf(exp->error_msg, "[ ${%s} = ", v->name);
        print_parsed_as_constant(exp->error_msg, n);
        buffer_strcat(exp->error_msg, " ] ");
        return n;
    }

    *error = EVAL_ERROR_UNKNOWN_VARIABLE;
    buffer_sprintf(exp->error_msg, "[ undefined variable '%s' ] ", v->name);
    return NAN;
}