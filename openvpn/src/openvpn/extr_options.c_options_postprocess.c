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
struct options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  options_postprocess_filechecks (struct options*) ; 
 int /*<<< orphan*/  options_postprocess_mutate (struct options*) ; 
 int /*<<< orphan*/  options_postprocess_verify (struct options*) ; 

void
options_postprocess(struct options *options)
{
    options_postprocess_mutate(options);
    options_postprocess_verify(options);
#ifndef ENABLE_SMALL
    options_postprocess_filechecks(options);
#endif /* !ENABLE_SMALL */
}