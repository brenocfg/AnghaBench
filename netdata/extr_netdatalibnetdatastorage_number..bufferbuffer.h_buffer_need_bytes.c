#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; size_t len; } ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_increase (TYPE_1__*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void buffer_need_bytes(BUFFER *buffer, size_t needed_free_size) {
    if(unlikely(buffer->size - buffer->len < needed_free_size))
        buffer_increase(buffer, needed_free_size);
}