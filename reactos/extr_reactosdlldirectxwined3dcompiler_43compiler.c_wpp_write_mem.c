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
 int BUFFER_INITIAL_CAPACITY ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 char* wpp_output ; 
 int wpp_output_capacity ; 
 unsigned int wpp_output_size ; 

__attribute__((used)) static void wpp_write_mem(const char *buffer, unsigned int len)
{
    char *new_wpp_output;

    if(wpp_output_capacity == 0)
    {
        wpp_output = HeapAlloc(GetProcessHeap(), 0, BUFFER_INITIAL_CAPACITY);
        if(!wpp_output)
            return;

        wpp_output_capacity = BUFFER_INITIAL_CAPACITY;
    }
    if(len > wpp_output_capacity - wpp_output_size)
    {
        while(len > wpp_output_capacity - wpp_output_size)
        {
            wpp_output_capacity *= 2;
        }
        new_wpp_output = HeapReAlloc(GetProcessHeap(), 0, wpp_output,
                                     wpp_output_capacity);
        if(!new_wpp_output)
        {
            ERR("Error allocating memory\n");
            return;
        }
        wpp_output = new_wpp_output;
    }
    memcpy(wpp_output + wpp_output_size, buffer, len);
    wpp_output_size += len;
}