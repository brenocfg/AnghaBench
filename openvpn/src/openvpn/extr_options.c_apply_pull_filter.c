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
struct pull_filter {scalar_t__ type; int /*<<< orphan*/  size; int /*<<< orphan*/  pattern; struct pull_filter* next; } ;
struct options {TYPE_1__* pull_filter_list; } ;
struct TYPE_2__ {struct pull_filter* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_LOW ; 
 int /*<<< orphan*/  D_PUSH ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ PUF_TYPE_ACCEPT ; 
 scalar_t__ PUF_TYPE_IGNORE ; 
 scalar_t__ PUF_TYPE_REJECT ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throw_signal_soft (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
apply_pull_filter(const struct options *o, char *line)
{
    struct pull_filter *f;

    if (!o->pull_filter_list)
    {
        return true;
    }

    for (f = o->pull_filter_list->head; f; f = f->next)
    {
        if (f->type == PUF_TYPE_ACCEPT && strncmp(line, f->pattern, f->size) == 0)
        {
            msg(D_LOW, "Pushed option accepted by filter: '%s'", line);
            return true;
        }
        else if (f->type == PUF_TYPE_IGNORE && strncmp(line, f->pattern, f->size) == 0)
        {
            msg(D_PUSH, "Pushed option removed by filter: '%s'", line);
            *line = '\0';
            return true;
        }
        else if (f->type == PUF_TYPE_REJECT && strncmp(line, f->pattern, f->size) == 0)
        {
            msg(M_WARN, "Pushed option rejected by filter: '%s'. Restarting.", line);
            *line = '\0';
            throw_signal_soft(SIGUSR1, "Offending option received from server");
            return false;
        }
    }
    return true;
}