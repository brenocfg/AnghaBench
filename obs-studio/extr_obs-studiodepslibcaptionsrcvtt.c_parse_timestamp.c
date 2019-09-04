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
typedef  int /*<<< orphan*/  utf8_char_t ;

/* Variables and functions */
 double VTTTIME2SECONDS (double,int,int,int) ; 
 int sscanf (int /*<<< orphan*/  const*,char*,int*,int*,int*,...) ; 

double parse_timestamp(const utf8_char_t* line)
{
    int hh, mm, ss, ms;
    if (sscanf(line, "%d:%2d:%2d%*1[,.]%3d", &hh, &mm, &ss, &ms) == 4) {
        return VTTTIME2SECONDS(hh, mm, ss, ms);
    }
    if (sscanf(line, "%2d:%2d%*1[,.]%3d", &mm, &ss, &ms) == 3) {
        return VTTTIME2SECONDS(0.0, mm, ss, ms);
    }
    return -1.0;
}