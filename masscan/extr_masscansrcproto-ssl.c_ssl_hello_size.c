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

unsigned
ssl_hello_size(const void *templ)
{
    const unsigned char *px = (const unsigned char *)templ;
    size_t template_size;
    
    template_size = (px[3]<<8 | px[4]) + 5;
    
    return (unsigned)template_size;
}