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
typedef  int /*<<< orphan*/  tjscalingfactor ;

/* Variables and functions */
 int /*<<< orphan*/  JMSG_LENGTH_MAX ; 
 int NUMSF ; 
 int /*<<< orphan*/  errStr ; 
 scalar_t__ sf ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

tjscalingfactor *tjGetScalingFactors(int *numscalingfactors)
{
  if (numscalingfactors == NULL) {
		snprintf(errStr, JMSG_LENGTH_MAX,
			"tjGetScalingFactors(): Invalid argument");
		return NULL;
	}

	*numscalingfactors=NUMSF;
	return (tjscalingfactor *)sf;
}