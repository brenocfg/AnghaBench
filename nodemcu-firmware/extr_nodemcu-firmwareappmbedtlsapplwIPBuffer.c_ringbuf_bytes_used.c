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
struct ringbuf_t {int dummy; } ;

/* Variables and functions */
 size_t ringbuf_bytes_free (struct ringbuf_t const*) ; 
 size_t ringbuf_capacity (struct ringbuf_t const*) ; 

size_t ringbuf_bytes_used(const struct ringbuf_t *rb)
{
	return ringbuf_capacity(rb) - ringbuf_bytes_free(rb);
}