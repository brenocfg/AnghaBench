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
struct TYPE_2__ {int /*<<< orphan*/  multiline; int /*<<< orphan*/  fp; } ;
struct in_src {scalar_t__ type; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int BOOL_CAST (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_TYPE_BUF ; 
 scalar_t__ IS_TYPE_FP ; 
 int buf_parse (int /*<<< orphan*/ ,char,char*,int const) ; 
 int /*<<< orphan*/  fgets (char*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static bool
in_src_get(const struct in_src *is, char *line, const int size)
{
    if (is->type == IS_TYPE_FP)
    {
        return BOOL_CAST(fgets(line, size, is->u.fp));
    }
    else if (is->type == IS_TYPE_BUF)
    {
        bool status = buf_parse(is->u.multiline, '\n', line, size);
        if ((int) strlen(line) + 1 < size)
        {
            strcat(line, "\n");
        }
        return status;
    }
    else
    {
        ASSERT(0);
        return false;
    }
}