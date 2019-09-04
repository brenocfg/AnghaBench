#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {char* text; int line; int column; int position; } ;
typedef  TYPE_1__ json_error_t ;

/* Variables and functions */
 int JSON_ERROR_TEXT_LENGTH ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void jsonp_error_vset(json_error_t *error, int line, int column,
                      size_t position, const char *msg, va_list ap)
{
    if(!error)
        return;

    if(error->text[0] != '\0') {
        /* error already set */
        return;
    }

    error->line = line;
    error->column = column;
    error->position = (int)position;

    vsnprintf(error->text, JSON_ERROR_TEXT_LENGTH, msg, ap);
    error->text[JSON_ERROR_TEXT_LENGTH - 1] = '\0';
}