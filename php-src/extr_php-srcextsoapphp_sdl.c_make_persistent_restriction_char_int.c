#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sdlRestrictionCharPtr ;
typedef  int /*<<< orphan*/  sdlRestrictionChar ;
struct TYPE_5__ {int /*<<< orphan*/  fixed; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void make_persistent_restriction_char_int(sdlRestrictionCharPtr *rest)
{
	sdlRestrictionCharPtr prest = NULL;

	prest = malloc(sizeof(sdlRestrictionChar));
	memset(prest, 0, sizeof(sdlRestrictionChar));
	prest->value = strdup((*rest)->value);
	prest->fixed = (*rest)->fixed;
	*rest = prest;
}