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

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 char* wpp_output ; 
 int wpp_output_size ; 

__attribute__((used)) static int wpp_close_output(void)
{
    char *new_wpp_output = HeapReAlloc(GetProcessHeap(), 0, wpp_output,
                                       wpp_output_size + 1);
    if(!new_wpp_output) return 0;
    wpp_output = new_wpp_output;
    wpp_output[wpp_output_size]='\0';
    wpp_output_size++;
    return 1;
}