#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum ListSpecifier { ____Placeholder_ListSpecifier } ListSpecifier ;
struct TYPE_4__ {char** sel; int /*<<< orphan*/  in_pixels; } ;
typedef  TYPE_1__ SharedFontSelData ;
typedef  int Boolean ;

/* Variables and functions */
#define  ENCODING 131 
#define  NAME 130 
#define  SIZE 129 
#define  STYLE 128 
 int TEMP_BUF_SIZE ; 
 int True ; 
 int /*<<< orphan*/  encoding_part (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  name_part (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  size_part (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  style_part (int /*<<< orphan*/ ,char*) ; 
 char* wild ; 

__attribute__((used)) static Boolean
match(SharedFontSelData *data, enum ListSpecifier l, int i)
{
    char buf[TEMP_BUF_SIZE];

    /* An empty selection or a wild card matches anything.
     */
    if (!data->sel[l] || !strcmp(data->sel[l], wild))
	return True;

    /* chunk out the desired part... */
    switch (l)
    {
	case ENCODING:
	    encoding_part(fn(data, i), buf);
	    break;

	case NAME:
	    name_part(fn(data, i), buf);
	    break;

	case STYLE:
	    style_part(fn(data, i), buf);
	    break;

	case SIZE:
	    size_part(fn(data, i), buf, data->in_pixels);
	    break;
	default:
	    ;
    }

    /* ...and chew it now */

    return !strcmp(buf, data->sel[l]);
}