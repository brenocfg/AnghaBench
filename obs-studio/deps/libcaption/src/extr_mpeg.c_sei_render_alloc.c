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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sei_t ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (size_t) ; 
 size_t sei_render (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t sei_render_size (int /*<<< orphan*/ *) ; 

uint8_t* sei_render_alloc(sei_t* sei, size_t* size)
{
    size_t aloc = sei_render_size(sei);
    uint8_t* data = malloc(aloc);
    (*size) = sei_render(sei, data);
    return data;
}