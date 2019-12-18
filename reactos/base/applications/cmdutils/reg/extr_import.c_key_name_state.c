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
struct parser {int dummy; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE_KEY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  STRING_OPEN_KEY_FAILED ; 
 scalar_t__ open_key (struct parser*,char*) ; 
 int /*<<< orphan*/  output_message (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 
 char* strrchrW (char*,char) ; 

__attribute__((used)) static WCHAR *key_name_state(struct parser *parser, WCHAR *pos)
{
    WCHAR *p = pos, *key_end;

    if (*p == ' ' || *p == '\t' || !(key_end = strrchrW(p, ']')))
        goto done;

    *key_end = 0;

    if (*p == '-')
    {
        set_state(parser, DELETE_KEY);
        return p + 1;
    }
    else if (open_key(parser, p) != ERROR_SUCCESS)
        output_message(STRING_OPEN_KEY_FAILED, p);

done:
    set_state(parser, LINE_START);
    return p;
}