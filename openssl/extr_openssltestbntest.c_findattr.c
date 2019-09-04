#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* value; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {int numpairs; TYPE_2__* pairs; } ;
typedef  TYPE_1__ STANZA ;
typedef  TYPE_2__ PAIR ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const char *findattr(STANZA *s, const char *key)
{
    int i = s->numpairs;
    PAIR *pp = s->pairs;

    for ( ; --i >= 0; pp++)
        if (strcasecmp(pp->key, key) == 0)
            return pp->value;
    return NULL;
}