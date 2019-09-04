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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  verb; } ;

/* Variables and functions */
 TYPE_1__* menuMap ; 
 int menuMapSize ; 
 char* nameStrip (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
lookupVerb(
	char	*verb,
	int	skip)		/* number of matches to skip */
{
    int		i;		/* loop iterator */

    for (i = 0; i < menuMapSize; i++)
	if (strcmp(menuMap[i].verb, verb) == 0 && skip-- == 0)
	    return nameStrip(menuMap[i].name);

    return NULL;
}