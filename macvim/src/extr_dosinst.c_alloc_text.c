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
struct TYPE_2__ {int /*<<< orphan*/ * text; } ;

/* Variables and functions */
 int /*<<< orphan*/ * alloc (int) ; 
 TYPE_1__* choices ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
alloc_text(int idx, char *fmt, char *arg)
{
    if (choices[idx].text != NULL)
	free(choices[idx].text);

    choices[idx].text = alloc((int)(strlen(fmt) + strlen(arg)) - 1);
    sprintf(choices[idx].text, fmt, arg);
}