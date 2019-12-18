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
struct lexret {int /*<<< orphan*/  function; int /*<<< orphan*/  proto; } ;
struct MacroDesc {scalar_t__ isBool; int /*<<< orphan*/  fn; int /*<<< orphan*/  arguments; int /*<<< orphan*/ * alias; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int BOOL_FUNCTION ; 
 int EMPTY ; 
 int VOID_FUNCTION ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int MACRO_DoLookUp(struct MacroDesc* start, const char* name, struct lexret* lr, unsigned len)
{
    struct MacroDesc*   md;

    for (md = start; md->name && len != 0; md++, len--)
    {
        if (strcasecmp(md->name, name) == 0 || (md->alias != NULL && strcasecmp(md->alias, name) == 0))
        {
            lr->proto = md->arguments;
            lr->function = md->fn;
            return md->isBool ? BOOL_FUNCTION : VOID_FUNCTION;
        }
    }
    return EMPTY;
}