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
typedef  int /*<<< orphan*/  u8 ;
struct trace_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err_text ; 
 int /*<<< orphan*/  last_cmd ; 
 int /*<<< orphan*/  last_cmd_loc ; 
 int /*<<< orphan*/  tracing_log_err (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hist_err(struct trace_array *tr, u8 err_type, u8 err_pos)
{
	tracing_log_err(tr, last_cmd_loc, last_cmd, err_text,
			err_type, err_pos);
}