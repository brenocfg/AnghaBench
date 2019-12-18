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
struct options {int exit_event_initial_state; int /*<<< orphan*/  config; int /*<<< orphan*/ * exit_event_name; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  WSO_FORCE_CONSOLE ; 
 int /*<<< orphan*/  WSO_FORCE_SERVICE ; 
 scalar_t__ WSO_MODE_CONSOLE ; 
 TYPE_1__ win32_signal ; 
 int /*<<< orphan*/  win32_signal_open (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  window_title ; 
 int /*<<< orphan*/  window_title_generate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_title_save (int /*<<< orphan*/ *) ; 

void
pre_setup(const struct options *options)
{
#ifdef _WIN32
    if (options->exit_event_name)
    {
        win32_signal_open(&win32_signal,
                          WSO_FORCE_SERVICE,
                          options->exit_event_name,
                          options->exit_event_initial_state);
    }
    else
    {
        win32_signal_open(&win32_signal,
                          WSO_FORCE_CONSOLE,
                          NULL,
                          false);

        /* put a title on the top window bar */
        if (win32_signal.mode == WSO_MODE_CONSOLE)
        {
            window_title_save(&window_title);
            window_title_generate(options->config);
        }
    }
#endif /* ifdef _WIN32 */
}