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
struct mem_file_desc {scalar_t__ pos; scalar_t__ buffer; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,scalar_t__,unsigned int) ; 
 unsigned int min (unsigned int,scalar_t__) ; 

__attribute__((used)) static int wpp_read_mem(void *file, char *buffer, unsigned int len)
{
    struct mem_file_desc *desc = file;

    len = min(len, desc->size - desc->pos);
    memcpy(buffer, desc->buffer + desc->pos, len);
    desc->pos += len;
    return len;
}