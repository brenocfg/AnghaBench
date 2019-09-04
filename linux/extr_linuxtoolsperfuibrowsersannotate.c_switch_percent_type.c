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
struct annotation_options {int percent_type; } ;

/* Variables and functions */
#define  PERCENT_HITS_GLOBAL 131 
#define  PERCENT_HITS_LOCAL 130 
#define  PERCENT_PERIOD_GLOBAL 129 
#define  PERCENT_PERIOD_LOCAL 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void
switch_percent_type(struct annotation_options *opts, bool base)
{
	switch (opts->percent_type) {
	case PERCENT_HITS_LOCAL:
		if (base)
			opts->percent_type = PERCENT_PERIOD_LOCAL;
		else
			opts->percent_type = PERCENT_HITS_GLOBAL;
		break;
	case PERCENT_HITS_GLOBAL:
		if (base)
			opts->percent_type = PERCENT_PERIOD_GLOBAL;
		else
			opts->percent_type = PERCENT_HITS_LOCAL;
		break;
	case PERCENT_PERIOD_LOCAL:
		if (base)
			opts->percent_type = PERCENT_HITS_LOCAL;
		else
			opts->percent_type = PERCENT_PERIOD_GLOBAL;
		break;
	case PERCENT_PERIOD_GLOBAL:
		if (base)
			opts->percent_type = PERCENT_HITS_GLOBAL;
		else
			opts->percent_type = PERCENT_PERIOD_LOCAL;
		break;
	default:
		WARN_ON(1);
	}
}