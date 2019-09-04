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
struct record_opts {int dummy; } ;

/* Variables and functions */
 int record_opts__config_freq (struct record_opts*) ; 

int record_opts__config(struct record_opts *opts)
{
	return record_opts__config_freq(opts);
}