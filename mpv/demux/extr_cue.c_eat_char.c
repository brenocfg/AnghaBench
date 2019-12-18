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
struct bstr {char* start; scalar_t__ len; } ;

/* Variables and functions */
 struct bstr bstr_cut (struct bstr,int) ; 

__attribute__((used)) static bool eat_char(struct bstr *data, char ch)
{
    if (data->len && data->start[0] == ch) {
        *data = bstr_cut(*data, 1);
        return true;
    } else {
        return false;
    }
}