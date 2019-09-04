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
struct mem_file_desc {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,struct mem_file_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_file_desc*) ; 
 int /*<<< orphan*/  ID3DInclude_Close (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ current_include ; 
 struct mem_file_desc current_shader ; 

__attribute__((used)) static void wpp_close_mem(void *file)
{
    struct mem_file_desc *desc = file;

    if(desc != &current_shader)
    {
        if(current_include)
            ID3DInclude_Close(current_include, desc->buffer);
        else
            ERR("current_include == NULL, desc == %p, buffer = %s\n",
                desc, desc->buffer);

        HeapFree(GetProcessHeap(), 0, desc);
    }
}