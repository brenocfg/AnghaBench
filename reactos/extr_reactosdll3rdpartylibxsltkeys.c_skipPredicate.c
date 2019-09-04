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
typedef  char xmlChar ;

/* Variables and functions */
 int skipString (char const*,int) ; 

__attribute__((used)) static int
skipPredicate(const xmlChar *cur, int end) {
    if ((cur == NULL) || (end < 0)) return(-1);
    if (cur[end] != '[') return(end);
    end++;
    while (cur[end] != 0) {
        if ((cur[end] == '\'') || (cur[end] == '"')) {
	    end = skipString(cur, end);
	    if (end <= 0)
	        return(-1);
	    continue;
	} else if (cur[end] == '[') {
	    end = skipPredicate(cur, end);
	    if (end <= 0)
	        return(-1);
	    continue;
	} else if (cur[end] == ']')
	    return(end + 1);
	end++;
    }
    return(-1);
}