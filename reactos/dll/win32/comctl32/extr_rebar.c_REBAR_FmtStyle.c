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
typedef  int UINT ;
typedef  size_t INT ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 char** band_stylename ; 
 scalar_t__* line ; 
 int /*<<< orphan*/  strcat (scalar_t__*,char*) ; 

__attribute__((used)) static CHAR *
REBAR_FmtStyle( UINT style)
{
    INT i = 0;

    *line = 0;
    while (band_stylename[i]) {
	if (style & (1<<i)) {
	    if (*line != 0) strcat(line, " | ");
	    strcat(line, band_stylename[i]);
	}
	i++;
    }
    return line;
}