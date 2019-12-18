#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* start; scalar_t__ len; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 TYPE_1__ bstr0 (char*) ; 
 TYPE_1__ bstr_cut (TYPE_1__,scalar_t__) ; 
 int bstr_find (TYPE_1__,TYPE_1__) ; 

__attribute__((used)) static void disable_styles(bstr header)
{
    bstr style = bstr0("\nStyle: ");
    while (header.len) {
        int n = bstr_find(header, style);
        if (n < 0)
            break;
        header.start[n + 1] = '#'; // turn into a comment
        header = bstr_cut(header, n + style.len);
    }
}