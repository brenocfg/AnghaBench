#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct status_output {int dummy; } ;
struct context {int /*<<< orphan*/  sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  print_status (struct context const*,struct status_output*) ; 
 int /*<<< orphan*/  signal_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_close (struct status_output*) ; 
 struct status_output* status_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_sigusr2(const struct context *c)
{
    struct status_output *so = status_open(NULL, 0, M_INFO, NULL, 0);
    print_status(c, so);
    status_close(so);
    signal_reset(c->sig);
}